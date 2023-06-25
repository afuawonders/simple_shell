#include "shell.h"
char *getErrorMessage126(char **args);
char *getErrorMessage127(char **args);
/**
* getErrorMessage126 - Creates an error message for permission denied failures.
* @args: An array of arguments passed to the command.
* Return: The error string.
*/
char *getErrorMessage126(char **args)
{
char *error, *hist_str;
int len;
hist_str = intToString(hist);
if (!hist_str)
return (NULL);
len = calculateStringLength(name) + calculateStringLength(hist_str) +
calculateStringLength(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}
copyString(error, name);
concatenateStrings(error, ": ");
concatenateStrings(error, hist_str);
concatenateStrings(error, ": ");
concatenateStrings(error, args[0]);
concatenateStrings(error, ": Permission denied\n");
free(hist_str);
return (error);
}
/**
* getErrorMessage127 - Creates an error message for command not found failures.
* @args: An array of arguments passed to the command.
* Return: The error string.
*/
char *getErrorMessage127(char **args)
{
char *error, *hist_str;
int len;
hist_str = intToString(hist);
if (!hist_str)
return (NULL);
len = calculateStringLength(name) + calculateStringLength(hist_str) +
calculateStringLength(args[0]) + 16;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}
copyString(error, name);
concatenateStrings(error, ": ");
concatenateStrings(error, hist_str);
concatenateStrings(error, ": ");
concatenateStrings(error, args[0]);
concatenateStrings(error, ": not found\n");
free(hist_str);
return (error);
}
