#include "shell.h"
alias_t *appendAlias(alias_t **initial, char *name, char *number);
void releaseAliasList(alias_t *initial);
list_t *appendNode(list_t **initial, char *directory);
void releaseList(list_t *initial);
/**
* appendAlias - Adds a node to the end of a alias_t linked list.
* @initial: A pointer to the initial of the list_t list.
* @name: The name of the new alias to be added.
* @number: The number of the new alias to be added.
* Return: If an error occurs - NULL.
*         Otherwise - a pointer to the new node.
*/
alias_t *appendAlias(alias_t **initial, char *name, char *number)
{
alias_t *inode  = malloc(sizeof(alias_t));
alias_t *last;
if (!inode)
return (NULL);
inode->nextNode = NULL;
inode->name = malloc(sizeof(char) * (calculateStringLength(name) + 1));
if (!inode->name)
{
free(inode);
return (NULL);
}
inode->number = number;
copyString(inode->name, name);
if (*initial)
{
last = *initial;
while (last->nextNode != NULL)
last = last->nextNode;
last->nextNode = inode;
}
else
*initial = inode;
return (inode);
}
/**
* appendNode - Adds a node to the end of a list_t linked list.
* @initial: A pointer to the initial of the list_t list.
* @directory: The directoryectory path for the new node to contain.
* Return: If an error occurs - NULL.
*         Otherwise - a pointer to the new node.
*/
list_t *appendNode(list_t **initial, char *directory)
{
list_t *inode  = malloc(sizeof(list_t));
list_t *last;
if (!inode)
return (NULL);
inode->directory = directory;
inode->nextNode = NULL;
if (*initial)
{
last = *initial;
while (last->nextNode != NULL)
last = last->nextNode;
last->nextNode = inode;
}
else
*initial = inode;
return (inode);
}
/**
* releaseAliasList - Frees a alias_t linked list.
* @initial: THe initial of the alias_t list.
*/
void releaseAliasList(alias_t *initial)
{
alias_t *nextNode;
while (initial)
{
nextNode = initial->nextNode;
free(initial->name);
free(initial->number);
free(initial);
initial = nextNode;
}
}
/**
* releaseList - Frees a list_t linked list.
* @initial: The initial of the list_t list.
*/
void releaseList(list_t *initial)
{
list_t *nextNode;
while (initial)
{
nextNode = initial->nextNode;
free(initial->directory);
free(initial);
initial = nextNode;
}
}
