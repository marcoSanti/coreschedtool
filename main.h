#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <errno.h>

typedef enum {PID, TID} taskType_t;

typedef enum {FALSE, TRUE} bool;

typedef enum {CREATE_GROUP, ADD_TASK_TO_GROUP, CLEAR_TASK, PEEK_TASK} command;

//Required since the data structure is not present in sys/prctl.h
//probably a bug. might be deleted in future revision
typedef enum {PIDTYPE_PID,PIDTYPE_TGID,PIDTYPE_PGID,PIDTYPE_SID,PIDTYPE_MAX}pid_type;

typedef struct{
    pid_type TaskType; 
    command cmd;        //what the program will run
    bool verbose;
    int numberOfTask;
    int *listOfTask;
    int shareFromTask;
} cst_config;


cst_config * loadConfiguration(int argc, char* argv[]);

void printConfiguration(cst_config *conf);
void printHelp();
void handlePrctlError();

bool isInt(char *str);
void checkRoot();

void printCookies(cst_config * config);

void pushCookie();
