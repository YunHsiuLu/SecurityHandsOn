if export a new lib (ex. mysleep here)<br>
dynamic linker will link to mysleep instead of original sleep()<br>
but if gcc in static mode (gcc -static program -o P)<br>
P will run origin sleep() instead of mysleep<br>
* * *
if a process's RID and EID are different, the dynamic linker will **ignore** LD\_PRELOAD and LD\_LIBRARY\_PATH 
