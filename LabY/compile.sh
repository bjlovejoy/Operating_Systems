#limit number of threads that start
ulimit -u

#compile LabY
gcc -pthread -o smoker smoker.c

#automatically run shell
#./smoker
