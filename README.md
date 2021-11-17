# coreschedtool
A tool to manage core scheduling for linux tasks

# Usage
 
$coreschedtool [\<list of taskId\> | \-add \<list of taskid\>  -to \<taskid\> | -c \<list of task id\>] [-v] 

 \<list of task id\>: if no parameters are given, a new core scheduling group will be created with all task id listed separated by a space;

 -r \<fromTask\> \<toTask\>: If -r is set inside the \<list of task id\>, then a range of tasks will be used, calculated from \<fromTask\> to \<toTask\>;

 -add \<list of task id\> -to \<taskid\>: \<list of task id\> will be added to \<taskid\> core scheduling group;

 -c \<list of task id\>: remove the \<list of task id\> from the core scheduling group wich is currently inserted into;

 -v: a verbose output will be shown;
\*

# Installation

run $ make install