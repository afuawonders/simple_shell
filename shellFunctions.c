#include "shell.h"
int (*fetchBuiltinCommand(char *command))(char **arguments, char **front);
int exitShell(char **arguments, char **front);
int changeDirectory(char **arguments,
char __attribute__((__unused__)) **front);
int showHelp(char **arguments, char __attribute__((__unused__)) **front);
/**
* fetchBuiltinCommand - Matches a command with a corresponding
* shellby builtin function.
* @command: The command to match.
* Return: A function pointer to the corresponding builtin.
*/
int (*fetchBuiltinCommand(char *command))(char **arguments, char **front)
{
builtin_t funcs[] = {
{ "exit", exitShell },
{ "env", displayEnvironment },
{ "setenv", setEnvironmentVariable },
{ "unsetenv", unsetEnvironmentVariable },
{ "cd", changeDirectory },
{ "alias", handleAlias },
{ "help", showHelp },
{ NULL, NULL }
};
int i;
for (i = 0; funcs[i].name; i++)
{
if (compareStrings(funcs[i].name, command) == 0)
break;
}
return (funcs[i].function);
}
/**
* exitShell - Causes normal process termination
* for the shellby shell.
* @arguments: An array of arguments containing the exit value.
* @front: A double pointer to the beginning of arguments.
* Return: If there are no arguments - -3.
* If the given exit value is invalid - 2.
* O/w - exits with the given status value.
* Description: Upon returning -3, the program exits back in the main function.
*/
int exitShell(char **arguments, char **front)
{
int i, len_of_int = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
if (arguments[0])
{
if (arguments[0][0] == '+')
{
i = 1;
len_of_int++;
}
for (; arguments[0][i]; i++)
{
if (i <= len_of_int && arguments[0][i] >= '0' && arguments[0][i] <= '9')
num = (num * 10) + (arguments[0][i] - '0');
else
return (generateError(--arguments, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (generateError(--arguments, 2));
arguments -= 1;
releaseCommands(arguments, front);
releaseEnvironmentMemory();
releaseAliasList(aliases);
exit(num);
}
/**
* changeDirectory - Changes the current directory of the shellby process.
* @arguments: An array of arguments.
* @front: A double pointer to the beginning of arguments.
* Return: If the given string is not a directory - 2.
* If an error occurs - -1.
* Otherwise - 0.
*/
int changeDirectory(char **arguments, char __attribute__((__unused__)) **front)
{
char **dir_info, *new_line = "\n";
char *oldpwd = NULL, *pwd = NULL;
struct stat dir;
oldpwd = getcwd(oldpwd, 0);
if (!oldpwd)
return (-1);
if (arguments[0])
{
if (*(arguments[0]) == '-' || compareStrings(arguments[0], "--") == 0)
{
if ((arguments[0][1] == '-' && arguments[0][2] == '\0') ||
arguments[0][1] == '\0')
{
if (searchEnvironment("OLDPWD") != NULL)
(chdir(*searchEnvironment("OLDPWD") + 7));
}
else
{
free(oldpwd);
return (generateError(arguments, 2));
}
}
else
{
if (stat(arguments[0], &dir) == 0 && S_ISDIR(dir.st_mode)
&& ((dir.st_mode & S_IXUSR) != 0))
chdir(arguments[0]);
else
{
free(oldpwd);
return (generateError(arguments, 2));
}
}
}
else
{
if (searchEnvironment("HOME") != NULL)
chdir(*(searchEnvironment("HOME")) + 5);
}
pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);
dir_info = malloc(sizeof(char *) * 2);
if (!dir_info)
return (-1);
dir_info[0] = "OLDPWD";
dir_info[1] = oldpwd;
if (setEnvironmentVariable(dir_info, dir_info) == -1)
return (-1);
dir_info[0] = "PWD";
dir_info[1] = pwd;
if (setEnvironmentVariable(dir_info, dir_info) == -1)
return (-1);
if (arguments[0] && arguments[0][0] == '-' && arguments[0][1] != '-')
{
write(STDOUT_FILENO, pwd, calculateStringLength(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(oldpwd);
free(pwd);
free(dir_info);
return (0);
}
/**
* showHelp - Displays information about shellby builtin commands.
* @arguments: An array of arguments.
* @front: A pointer to the beginning of arguments.
* Return: If an error occurs - -1.
* Otherwise - 0.
*/
int showHelp(char **arguments, char __attribute__((__unused__)) **front)
{
if (!arguments[0])
displayHelpAll();
else if (compareStrings(arguments[0], "alias") == 0)
displayHelpAlias();
else if (compareStrings(arguments[0], "cd") == 0)
displayHelpCd();
else if (compareStrings(arguments[0], "exit") == 0)
displayHelpExit();
else if (compareStrings(arguments[0], "env") == 0)
printHelpEnv();
else if (compareStrings(arguments[0], "setenv") == 0)
printSetenv();
else if (compareStrings(arguments[0], "unsetenv") == 0)
printUnsetenv();
else if (compareStrings(arguments[0], "help") == 0)
printHelp();
else
write(STDERR_FILENO, name, calculateStringLength(name));
return (0);
}
