# Coreschedtool
A tool to manage core scheduling for linux tasks. This is achived by manipulating the task cookie using the prctl() function.

created by Marco Santimaria as part of his bachelor degree's thesis, supervised by [Dario Faggioli](https://github.com/dfaggioli) and [Enrico bini](https://github.com/ebni). 

### Compile the tool
this will compile the tool.
```
$ make coreschedtool
```
### Install
this will install the compiled software into the /usr/bin folder
```
$ make install
```
### Uninstall
this will remove the compiled software from the /usr/bin folder
```
$ make uninstall
```


## Usage
```
$coreschedtool [\<list of taskId\> | \-add \<list of taskid\>  -to \<taskid\> | -c \<list of task id\>] [-v] 
```
Parameter description:
 - <list of task id\>: if no parameters are given, a new core scheduling group will be created with all task id listed separated by a space;

 - -r \<fromTask\> \<toTask\>: If -r is set inside the \<list of task id\>, then a range of tasks will be used, calculated from \<fromTask\> to \<toTask\>;

 - -add \<list of task id\> -to \<taskid\>: \<list of task id\> will be added to \<taskid\> core scheduling group;

 - -c \<list of task id\>: remove the \<list of task id\> from the core scheduling group wich is currently inserted into;

- -v: a verbose output will be shown;


