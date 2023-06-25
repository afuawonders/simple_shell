#include "shell.h"
void sig_handler(int sig);
int executeCommand(char **args, char **front);
/**
* sig_handler - Prints a new prompt upon a signal.
* @sig: The signal.
*/
void sig_handler(int sig)
{
char *new_prompt = "\n$ ";
(void)sig;
signal(SIGINT, sig_handler);
write(STDIN_FILENO, new_prompt, 3);
}
/**
* executeCommand - executeCommands a command in a child process.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
* Return: If an error occurs - a corresponding error code.
*         O/w - The exit value of the last executeCommandd command.
*/
int executeCommand(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];
if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = getCommandLocation(command);
}
if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (generateError(args, 126));
else
ret = (generateError(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
execve(command, args, environ);
if (errno == EACCES)
ret = (generateError(args, 126));
releaseEnvironmentMemory();
releaseCommands(args, front);
releaseAliasList(aliases);
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}
/**
* main - Runs a simple UNIX command interpreter.
* @argc: The number of arguments supplied to the program.
* @argv: An array of pointers to the arguments.
* Return: The return value of the last executeCommandd command.
*/
int main(int argc, char *argv[])
{
int ret = 0, retn;
int *exe_ret = &retn;
char *prompt = "$ ", *new_line = "\n";
name = argv[0];
hist = 1;
aliases = NULL;
signal(SIGINT, sig_handler);
*exe_ret = 0;
environ = duplicateEnvironment();
if (!environ)
exit(-100);
if (argc != 1)
{
ret = executeCmdFromFile(argv[1], exe_ret);
releaseEnvironmentMemory();
releaseAliasList(aliases);
return (*exe_ret);
}
if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handleCommands(exe_ret);
releaseEnvironmentMemory();
releaseAliasList(aliases);
return (*exe_ret);
}
while (1)
{
write(STDOUT_FILENO, prompt, 2);
ret = handleCommands(exe_ret);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 1);
releaseEnvironmentMemory();
releaseAliasList(aliases);
exit(*exe_ret);
}
}
releaseEnvironmentMemory();
releaseAliasList(aliases);
return (*exe_ret);
}

