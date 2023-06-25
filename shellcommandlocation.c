#include "shell.h"
char *directoryPath(char *path);
list_t *getPathDirectories(char *path);
/**
* getCommandLocation - Locates a command in the PATH.
* @command: The command to locate.
* Return: If an error occurs or the command cannot be located - NULL.
*         Otherwise - the full pathname of the command.
*/
char *getCommandLocation(char *command)
{
char **path, *temp;
list_t *dirs, *head;
struct stat st;
path = searchEnvironment("PATH");
if (!path || !(*path))
return (NULL);
dirs = getPathDirectories(*path + 5);
head = dirs;
while (dirs)
{
temp = malloc(calculateStringLength(dirs->directory) +
calculateStringLength(command) + 2);
if (!temp)
return (NULL);
copyString(temp, dirs->directory);
concatenateStrings(temp, "/");
concatenateStrings(temp, command);
if (stat(temp, &st) == 0)
{
releaseList(head);
return (temp);
}
dirs = dirs->nextNode;
free(temp);
}
releaseList(head);
return (NULL);
}
/**
* directoryPath - Copies path but also replaces leading/sandwiched/trailing
*     colons (:) with current working directory.
* @path: The colon-separated list of directories.
* Return: A copy of path with any leading/sandwiched/trailing colons replaced
*	   with the current working directory.
*/
char *directoryPath(char *path)
{
int i, length = 0;
char *path_copy, *pwd;
pwd = *(searchEnvironment("PWD")) + 4;
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
length += calculateStringLength(pwd) + 1;
else
length++;
}
else
length++;
}
path_copy = malloc(sizeof(char) * (length + 1));
if (!path_copy)
return (NULL);
path_copy[0] = '\0';
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (i == 0)
{
concatenateStrings(path_copy, pwd);
concatenateStrings(path_copy, ":");
}
else if (path[i + 1] == ':' || path[i + 1] == '\0')
{
concatenateStrings(path_copy, ":");
concatenateStrings(path_copy, pwd);
}
else
concatenateStrings(path_copy, ":");
}
else
{
concatenateStringsWithLength(path_copy, &path[i], 1);
}
}
return (path_copy);
}
/**
* getPathDirectories - Tokenizes a colon-separated list of
*                directories into a list_s linked list.
* @path: The colon-separated list of directories.
* Return: A pointer to the initialized linked list.
*/
list_t *getPathDirectories(char *path)
{
int index;
char **dirs, *path_copy;
list_t *head = NULL;
path_copy = directoryPath(path);
if (!path_copy)
return (NULL);
dirs = customStrtok(path_copy, ":");
free(path_copy);
if (!dirs)
return (NULL);
for (index = 0; dirs[index]; index++)
{
if (appendNode(&head, dirs[index]) == NULL)
{
releaseList(head);
free(dirs);
return (NULL);
}
}
free(dirs);
return (head);
}
