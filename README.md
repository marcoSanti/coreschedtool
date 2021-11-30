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
$coreschedtool [-v] [\<list of taskId\> | \-add \<list of taskid\>  -to \<taskid\> | -c \<list of task id\>] [<executable>] 
```
Parameter description:
 - <list of task id\>: if no parameters are given, a new core scheduling group will be created with all task id listed separated by a space;

 - -r \<fromTask\> \<toTask\>: If -r is set inside the \<list of task id\>, then a range of tasks will be used, calculated from \<fromTask\> to \<toTask\>;

 - -add \<list of task id\> -to \<taskid\>: \<list of task id\> will be added to \<taskid\> core scheduling group;

 - -c \<list of task id\>: remove the \<list of task id\> from the core scheduling group wich is currently inserted into;

- -v: a verbose output will be shown;
- \<executable\> will run the executable command with core scheduling enabled


### Examples

```
$coreschedtool -v 1234 5678
```
This command will set core scheduling for tasks id 1234 and 5678 and will print verbose option

```
$coreschedtool -v -add 1011 -to 1234 
```
This command will add the task with tid 1011 to the task group of which 1234 is a member


```
$corechedtool -peek 1234
```
This command will show the core scheduling cookie assiged to task id 1234. If 0 is shown, no core scheduling is set for given task

```
$coreschedtool -v ping github.com
```
This command will run the command "ping github.com" with core scheduling enabled!



