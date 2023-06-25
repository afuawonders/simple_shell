#include "shell.h"
int handleAlias(char **arguments, char __attribute__((__unused__)) **front);
void defineShortcut(char *var_name, char *number);
void displayShortcut(alias_t *alias);
/**
* handleAlias - Builtin command that either prints all aliases, specific
* aliases, or sets an alias.
* @arguments: An array of arguments.
* @front: A double pointer to the beginning of arguments.
* Return: If an error occurs - -1.
*         Otherwise - 0.
*/
int handleAlias(char **arguments, char __attribute__((__unused__)) **front)
{
alias_t *temp = aliases;
int i, ret = 0;
char *number;
if (!arguments[0])
{
while (temp)
{
displayShortcut(temp);
temp = temp->nextNode;
}
return (ret);
}
for (i = 0; arguments[i]; i++)
{
temp = aliases;
number = findFirstOccurrence(arguments[i], '=');
if (!number)
{
while (temp)
{
if (compareStrings(arguments[i], temp->name) == 0)
{
displayShortcut(temp);
break;
}
temp = temp->nextNode;
}
if (!temp)
ret = generateError(arguments + i, 1);
}
else
defineShortcut(arguments[i], number);
}
return (ret);
}
/**
* defineShortcut - Will either set an existing alias 'name' with a new number,
* 'number' or creates a new alias with 'name' and 'number'.
* @var_name: Name of the alias.
* @number: number of the alias. First character is a '='.
*/
void defineShortcut(char *var_name, char *number)
{
alias_t *temp = aliases;
int len, j, k;
char *new_number;
*number = '\0';
number++;
len = calculateStringLength(number) - calculateStringSpan(number, "'\"");
new_number = malloc(sizeof(char) * (len + 1));
if (!new_number)
return;
for (j = 0, k = 0; number[j]; j++)
{
if (number[j] != '\'' && number[j] != '"')
new_number[k++] = number[j];
}
new_number[k] = '\0';
while (temp)
{
if (compareStrings(var_name, temp->name) == 0)
{
free(temp->number);
temp->number = new_number;
break;
}
temp = temp->nextNode;
}
if (!temp)
appendAlias(&aliases, var_name, new_number);
}
/**
* displayShortcut - Prints the alias in the format name='number'.
* @alias: Pointer to an alias.
*/
void displayShortcut(alias_t *alias)
{
char *alias_string;
int len = calculateStringLength(alias->name) +
calculateStringLength(alias->number) + 4;
alias_string = malloc(sizeof(char) * (len + 1));
if (!alias_string)
return;
copyString(alias_string, alias->name);
concatenateStrings(alias_string, "='");
concatenateStrings(alias_string, alias->number);
concatenateStrings(alias_string, "'\n");
write(STDOUT_FILENO, alias_string, len);
free(alias_string);
}
/**
* replaceAliases - Goes through the arguments and replace any matching alias
* with their number.
* @arguments: 2D pointer to the arguments.
* Return: 2D pointer to the arguments.
*/
char **replaceAliases(char **arguments)
{
alias_t *temp;
int i;
char *new_number;
if (compareStrings(arguments[0], "alias") == 0)
return (arguments);
for (i = 0; arguments[i]; i++)
{
temp = aliases;
while (temp)
{
if (compareStrings(arguments[i], temp->name) == 0)
{
new_number = malloc(sizeof(char) * (calculateStringLength(temp->number) + 1));
if (!new_number)
{
releaseCommands(arguments, arguments);
return (NULL);
}
copyString(new_number, temp->number);
free(arguments[i]);
arguments[i] = new_number;
i--;
break;
}
temp = temp->nextNode;
}
}
return (arguments);
}
