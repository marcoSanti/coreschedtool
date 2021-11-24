#include "main.h"

/*
this function reads the parameters and loads them into memory. 
on success a loadConfiguration is set, and on failure NULL is returned
*/

cst_config * loadConfiguration(int argc, char* argv[]){

    int parsedParams = 1; //begins from 1 because exec name is already evaluated in input parsing
   
    cst_config * config = malloc(sizeof(cst_config));

    if(config == NULL || argc == 1)
        return NULL;
    

    while(parsedParams < argc){
    
        if(isInt(argv[parsedParams])){ 
            
            int readTask = 0;
            config->listOfTask = malloc(0);

            do{
                config->listOfTask = realloc(config->listOfTask, (readTask+1) * sizeof(int));
                config->listOfTask[readTask] = atoi(argv[parsedParams]);
                parsedParams+=1;
                readTask++;
            }while((parsedParams < argc) && isInt(argv[parsedParams]));
            config->numberOfTask = readTask;

        }else if(strcmp(argv[parsedParams], "-r") == 0){ //if a range of pids is pecified to work with
            
            int from, to, rangeSize, pos=0;
          
            from = atoi(argv[parsedParams += 1]);
            to   = atoi(argv[parsedParams += 1]);
            rangeSize = to-from+1;

            config->listOfTask = malloc(rangeSize * sizeof(pid_t));

            while(pos<rangeSize){  //calulating all the threads id and putting them into an array
                config->listOfTask[pos] = from;
                from++;
                pos++;
            }

            config->numberOfTask = rangeSize;
            parsedParams++;

        }else if(strcmp(argv[parsedParams], "-add") == 0){ //if a cookie should be shared from a given task id

            int readTask = 0;
            parsedParams++;
            config->listOfTask = malloc(0);
            config->cmd = ADD_TASK_TO_GROUP;

            while((parsedParams < argc) && isInt(argv[parsedParams])){
                config->listOfTask = realloc(config->listOfTask, (readTask+1) * sizeof(int));
                config->listOfTask[readTask] = atoi(argv[parsedParams]);
                parsedParams++;
                readTask++;
            }

           if(strcmp(argv[parsedParams], "-to") !=0){
                printf("Error: no -to param specified. Cannot get destination task id!\n");
            }else{
                parsedParams++;
            }
            config->numberOfTask = readTask;
            config->shareFromTask = atoi(argv[parsedParams]);
            parsedParams++;
            

        }else if(strcmp(argv[parsedParams], "-clear") == 0){
            config->cmd = CLEAR_TASK;
            parsedParams++;

        }else if(strcmp(argv[parsedParams], "-peek") == 0){
            config->cmd = PEEK_TASK;
            parsedParams++;

        }else if(strcmp(argv[parsedParams], "-v") == 0){  //if is set, the output will be verbose.

            config->verbose = TRUE;
            parsedParams++;

        }else{
            //add the option to exec another program in core scheduling
            config->cmd = EXEC_TASK;
            config->execPosition = parsedParams;
            return config; //stop the parsing of the code.
        }

        
    }

    return config;
}


/*this function prints the program help*/
void printHelp(){
    printf("\ncoreschedtool, a tool to manage core scheduling cookies.\n");
    printf("developed by Marco Edoardo Santimaria as part of his thesis @ University of Torino (UniTo)\n");
    printf("Usage: $coreschedtool [<list of taskId> | -add <list of taskid>  -to <taskid>| -c <list of task id> | -peek <list of taskid>] [-v] \n");
    printf("\n<list of task id> : \n\tif no parameters are given, a new core scheduling group will be created with all task id listed, separated by a space\n");
    printf("\n-r <fromTask> <toTask>: \n\tIf -r is given as parameter instead of <list of task id>, then a range of tasks will be used\n\n");
    printf("\n-add <list of task id> -to <taskid>: \n\t<list of task id> will be added to <taskid> core scheduling group\n");
    printf("\n-c <list of task id> : \n\tremove the <list of task id> from the core scheduling group wich is currently inserted into\n");
    printf("\n-peek : \n\tprint all cookies from given tasks ids\n\n");
    printf("\n-v : \n\ta verbose output will be added\n\n");
    printf("\n\n");
}

/*this function tells wheter string is a int number*/
bool isInt(char *str){
    int i;
    for (i = 0; str[i] != 0; i++)
      if (!isdigit(str[i])) return FALSE;
    return TRUE;
}


/*this function prints the current tool configuration, as read from argv*/
void printConfiguration(cst_config *conf){
    int i;
    printf("\n\n|=========CONFIG========\n|\n| Command:\t%d\n| TaskType:\t%d\n| ShareFrom:\t%d\n| NumOfTasks:\t%d\n| Verbose:\t%d\n", 
            conf->cmd,
            conf->TaskType,
            conf->shareFromTask,
            conf->numberOfTask,
            conf->verbose 
    );
    printf("| Target tasks:\n");
    for(i=0; i< conf->numberOfTask;i++){
        printf("|\t\t%d\n", conf->listOfTask[i]);
    }
    printf("|\n|=======END CONFIG======\n\n");
}


/*Check whether user is root*/
void checkRoot(){  
    if(!(geteuid() == 0)){
        printf("\nError: command must be run as root!\n");
        printHelp();
        exit(EXIT_SUCCESS);
    }
}

/*
    This function prints all cookies values from the threads id given in the launch args
*/
void printCookies(cst_config * config){
    int i;
    unsigned long cookie = 0;
    extern int errno;

    printf("Task_ID\t\tCookie_value\n");

    for(i=0;i<config->numberOfTask;i++){
        if(prctl(PR_SCHED_CORE, PR_SCHED_CORE_GET, config->listOfTask[i], PIDTYPE_PID, &cookie) == -1)
            handlePrctlError();
        else
            printf("  %d\t\t%lu\n", config->listOfTask[i], cookie);
    }
    printf("\n");
    if(prctl(PR_SCHED_CORE, PR_SCHED_CORE_GET, getpid(), PIDTYPE_PID, &cookie) == -1)
        handlePrctlError();
    else
        printf("[ %d\t\t%lu ] <- coreschedtool temp cookieValue\n", getpid(), cookie);
}


void handlePrctlError(){
    extern int errno;
    extern cst_config* config;

    printf("An error has occured! aborting...\n");

    if(config->verbose){
         switch (errno){
            case EINVAL:
                /*arg1 is not recognised: no core sched available*/
                printf("Error: core scheduling not implemented!\n");
                break;

            case ENOMEM:
                /*unable to allocate memory*/
                printf("Error %d: %s\n", errno, strerror(errno));
                break;

            case ESRCH:
                printf("Error: target/source task id not found!\n");
                break;

            case EPERM:
                printf("Error: missing ptrace permissions\n");
                break;

            case ENODEV:
                printf("Error: your machine does not support SMT (Hyperthreading)\n");
                break;
            
            default:
                printf("Error not specific to core scheduling! Details:\n\t");
                printf("[Error: %d] : %s\n", errno, strerror(errno));
            
        }
    }
    exit(EXIT_FAILURE);
}

void pushCookie(){
    int i;
    extern cst_config* config;

    /* pushing my cookie to te others tasks*/
    for(i = 0; i< config->numberOfTask; i++)
        prctl(PR_SCHED_CORE, PR_SCHED_CORE_SHARE_TO, config->listOfTask[i], config->TaskType, NULL);
}


