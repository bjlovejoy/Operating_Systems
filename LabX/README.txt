Instructions for compiling and running the shell:

    1. Open the terminal.
    2. Navigate to the directory containg the file "ourshell.c"
    3. Type "./compile.sh" into the terminal, without quotations.
    4. Type "./ourshell.c" into the terminal, without quotations.


Instructions for using the shell:
    
    The shell functions just like the regular terminal. Regular linux
    terminal commands function as normal, with the exception that there
    are additional custom commands written for the shell.


List of custom commands:
    C file1 file2
        Copy; create file2, copy all bytes of file1 to file2 without
        deleting file1.
    D file 
        Delte the named file.
    E comment
        Echo; display comment on screen followed by a new line.
    H
        Help; display the user manual.
    L
        List the contents of the currents directory.
    M file
        Make; create the named text file by launcing a text editor.
    P file
        Print; display the contents of the named file on screen.
    Q 
        Quit the shell.
    S 
        Surf the web by launching firefox as a background process.
    W 
        Wipe; clear the screen.
    X program
        Execute the named program.
        
    
The purpose of this lab was to make a simple shell that parsed custom commands and executed Linux userspace programs based off of the commands and arguments that were entered, and output an error message when an incorrect command or number of arguments were entered. In addition to this functionality, the shell also had to allow for execution of regular Linux commands, and it had to fork another process to execute programs.

The given initial file, capitalist myshell.c, made the implementation of this shell functionality fairly straightforward; it contained the code necessary for calling execvp() to load a program, forking the process to execute console programs, and waiting for the execution of the programs to finish. The communist version, ourshell.c, contains the modifications necessary to accept the parsed commands and arguments, then make decisions based on the validity of the input. The main way this was implemented was to modify the command name string before it was passed to the execvp function call. If the command name did not match any of the internal commands, then it would still be passed to execvp(), which tacitly allowed for functionality of regular Linux commands. Other smaller edits were made to straighen out kinks, like changing the prompt string, adding a separate function for browsing the internet in the background, adding a help manual, and returning 0 from the main function directly from the "Q" case in the switch(command.name[0]) block to keep the shell from forking a new process.

Overall, the lab provided more experience with the execvp() and fork() functions along with more knowledge of the Linux shell, so it can be regarded as rewarding and successful.
