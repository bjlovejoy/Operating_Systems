Brendon Lovejoy, Corey Miller, Colin Frame
bjl66@zips.uakron.edu
Operating Systems
Lab 5

The purpose of this lab was to build the foundation for a shell that will parse commands and run programs based off of the commands that were entered. Firstly, the shell program had to be called from the kernel. Next, came the fun part- writing the shell itself. In the beginning of writing the shell, a mechanism for printing a pig on every new line was written. Something worth noting here is that the OS is modular by design, so even though we aren't writing kernel code, we can still use it when needed via interrupt 33. This way, if those functions need to be changed, they can be modified in the kernel rather than needing to be rewritten for every program that uses them.

With those things in mind, the parser was written, which was in the form of handleCommands and compareCommands. The former was written to take strings input from the user, and then format the data in a way that could be interpreted by compareCommands. When a particular command was entered, compareCommands would look at what the command was and its arguments, and then run particular functionality based off of the command. For example, boot will call interrupt 25 to reboot the computer. Other than boot, clrs, and echo, the functionality for the other commands was not implemented yet. However, a mechanism for detecting a valid command along with a valid number of arguments was written such that an error message would be printed if an invalid command was entered or if an invalid number of arguments was input. 

This lab serves as the foundation for what is probably the majority of userspace programming in this project, and since the code works, it can be regarded as a successful and educational lab.
