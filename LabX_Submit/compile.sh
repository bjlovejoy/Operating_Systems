#limit number of threads that start
ulimit -u

#compile myshell
gcc -o ourshell ourshell.c

#compile help (operator's manual test)
#gcc -o helpMan helpMan.c

#automatically run shell
#./ourshell
