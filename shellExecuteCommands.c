#include "shell.h"
char *getArguments(char *line, int *exe_ret);
int executeCommands(char **args, char **front, int *exe_ret);
int runCommands(char **args, char **front, int *exe_ret);
int handleCommands(int *exe_ret);
int validateCommands(char **args);
/**
* getArguments - Gets a command from standard input.
* @line: A buffer to store the command.
* @exe_ret: The return value of the last executeCommandd command.
* Return: If an error occurs - NULL.
*   Otherwise - a pointer to the stored command.
*/
char *getArguments(char *line, int *exe_ret)
{
size_t n = 0;
ssize_t read;
char *prompt = "$ ";
if (line)
free(line);
read = safeGetLine(&line, &n, STDIN_FILENO);
if (read == -1)
return (NULL);
if (read == 1)
{
hist++;
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, prompt, 2);
return (getArguments(line, exe_ret));
}
line[read - 1] = '\0';
substituteVariables(&line, exe_ret);
processLine(&line, read);
return (line);
}
/**
* executeCommands - Partitions operators from commands and calls them.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
* @exe_ret: The return value of the parent process last executeCommandd command
* Return: The return value of the last executeCommandd command.
*/
int executeCommands(char **args, char **front, int *exe_ret)
{
int ret, index;
if (!args[0])
return (*exe_ret);
for (index = 0; args[index]; index++)
{
if (compareStringsWithLength(args[index], "||", 2) == 0)
{
free(args[index]);
args[index] = NULL;
args = replaceAliases(args);
ret = runCommands(args, front, exe_ret);
if (*exe_ret != 0)
{
args = &args[++index];
index = 0;
}
else
{
for (index++; args[index]; index++)
free(args[index]);
return (ret);
}
}
else if (compareStringsWithLength(args[index], "&&", 2) == 0)
{
free(args[index]);
args[index] = NULL;
args = replaceAliases(args);
ret = runCommands(args, front, exe_ret);
if (*exe_ret == 0)
{
args = &args[++index];
index = 0;
}
else
{
for (index++; args[index]; index++)
free(args[index]);
return (ret);
}
}
}
args = replaceAliases(args);
ret = runCommands(args, front, exe_ret);
return (ret);
}
/**
* runCommands - Calls the execution of a command.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
* @exe_ret: The return value of the parent process last executeCommandd command
* Return: The return value of the last executeCommandd command.
*/
int runCommands(char **args, char **front, int *exe_ret)
{
int ret, i;
int (*builtin)(char **args, char **front);
builtin = fetchBuiltinCommand(args[0]);
if (builtin)
{
ret = builtin(args + 1, front);
if (ret != EXIT)
*exe_ret = ret;
}
else
{
*exe_ret = executeCommand(args, front);
ret = *exe_ret;
}
hist++;
for (i = 0; args[i]; i++)
free(args[i]);
return (ret);
}
/**
* handleCommands - Gets, calls, and runs the execution of a command.
* @exe_ret: The return value of the parent process last executeCommandd command
* Return: If an end-of-file is read - END_OF_FILE (-2).
* If the input cannot be tokenized - -1.
* O/w - The exit value of the last executeCommandd command.
*/
int handleCommands(int *exe_ret)
{
int ret = 0, index;
char **args, *line = NULL, **front;
line = getArguments(line, exe_ret);
if (!line)
return (END_OF_FILE);
args = customStrtok(line, " ");
free(line);
if (!args)
return (ret);
if (validateCommands(args) != 0)
{
*exe_ret = 2;
releaseCommands(args, args);
return (*exe_ret);
}
front = args;
for (index = 0; args[index]; index++)
{
if (compareStringsWithLength(args[index], ";", 1) == 0)
{
free(args[index]);
args[index] = NULL;
ret = executeCommands(args, front, exe_ret);
args = &args[++index];
index = 0;
}
}
if (args)
ret = executeCommands(args, front, exe_ret);
free(front);
return (ret);
}
/**
* validateCommands - Checks if there are any leading ';', ';;', '&&', or '||'.
* @args: 2D pointer to tokenized commands and arguments.
* Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
* Otherwise - 0.
*/
int validateCommands(char **args)
{
size_t i;
char *cur, *nex;
for (i = 0; args[i]; i++)
{
cur = args[i];
if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
{
if (i == 0 || cur[1] == ';')
return (generateError(&args[i], 2));
nex = args[i + 1];
if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
return (generateError(&args[i + 1], 2));
}
}
return (0);
}
