#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <errno.h>
#include <linux/version.h>


typedef enum {PID, TID} taskType_t;

typedef enum {FALSE, TRUE} bool;

typedef enum {CREATE_GROUP, ADD_TASK_TO_GROUP, CLEAR_TASK, PEEK_TASK, EXEC_TASK} command;

typedef struct{
    int coreScope;       //scope to which the operation will apply
    command cmd;        //what the program will run
    bool verbose;
    int numberOfTask;
    int *listOfTask;
    int shareFromTask;
    int execPosition;
} cst_config;


cst_config * loadConfiguration(int argc, char* argv[]);

void printConfiguration(cst_config *conf);
void printHelp();
void handlePrctlError();

bool isInt(char *str);
void checkRoot();

void printCookies(cst_config * config);

void pushCookie();
