#include "shell.h"
int num_len(int num);
char *intToString(int num);
int generateError(char **args, int err);
/**
* num_len - Counts the digit length of a number.
* @num: The number to measure.
* Return: The digit length.
*/
int num_len(int num)
{
unsigned int num1;
int len = 1;
if (num < 0)
{
len++;
num1 = num * -1;
}
else
{
num1 = num;
}
while (num1 > 9)
{
len++;
num1 /= 10;
}
return (len);
}
/**
* intToString - Converts an integer to a string.
* @num: The integer.
* Return: The converted string.
*/
char *intToString(int num)
{
char *buffer;
int len = num_len(num);
unsigned int num1;
buffer = malloc(sizeof(char) * (len + 1));
if (!buffer)
return (NULL);
buffer[len] = '\0';
if (num < 0)
{
num1 = num * -1;
buffer[0] = '-';
}
else
{
num1 = num;
}
len--;
do {
buffer[len] = (num1 % 10) + '0';
num1 /= 10;
len--;
} while (num1 > 0);
return (buffer);
}
/**
* generateError - Writes a custom error message to stderr.
* @args: An array of arguments.
* @err: The error value.
* Return: The error value.
*/
int generateError(char **args, int err)
{
char *error;
switch (err)
{
case -1:
error = getErrorEnv(args);
break;
case 1:
error = getErrorMessage1(args);
break;
case 2:
if (*(args[0]) == 'e')
error = getErrorMessage2Exit(++args);
else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
error = getErrorMessage2Syntax(args);
else
error = getErrorMessage2Cd(args);
break;
case 126:
error = getErrorMessage126(args);
break;
case 127:
error = getErrorMessage127(args);
break;
}
write(STDERR_FILENO, error, calculateStringLength(error));
if (error)
free(error);
return (err);
}
