#include "main.h"


/*global vars*/

cst_config *config;


int main(int argc, char* argv[]){
    extern int errno;
    int i = 0, command = 0;
    unsigned long cookie;

    checkRoot();

    if((config = loadConfiguration(argc, argv))==NULL){
        printHelp();
        exit(EXIT_FAILURE);
    }

    //ckeck that no error returns from prctl() to ensure that CORE SCHEDULING returns no errors
    if(prctl(PR_SCHED_CORE, PR_SCHED_CORE_GET, config->listOfTask[i], PIDTYPE_PID, &cookie) == -1)
        handlePrctlError();
    

    /*
        Since an api that allows to directly push a cookie to a certain task i not available,
        Firstly tis program must be added to the target core scheduling group, and
        then add the <list of task id> tasks to the group
    */
        
    switch (config->cmd)
    {
    case CREATE_GROUP:
        prctl(PR_SCHED_CORE, PR_SCHED_CORE_CREATE, getpid(), config->TaskType, NULL);
        pushCookie();
        break;

    case ADD_TASK_TO_GROUP:
        prctl(PR_SCHED_CORE, PR_SCHED_CORE_SHARE_FROM, config->shareFromTask , config->TaskType, NULL);
        pushCookie();
        break;

    case CLEAR_TASK:
        pushCookie();
        break;
    
    default:
        printf("Error: unknown prctl command\n");
        printConfiguration(config);
        exit(EXIT_FAILURE);
        break;
    }

    
    if(config->verbose){
        printConfiguration(config);
        printCookies(config);
    }
   
    exit(EXIT_SUCCESS);
}