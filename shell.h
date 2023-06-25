#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#define END_OF_FILE -2
#define EXIT -3
/* Global environemnt */
extern char **environ;
/**
* struct list_s - A new struct type defining a linked list.
* @directory: A directory path.
* @next: A pointer to another struct list_s.
*/
typedef struct list_s
i{
char *directory;
struct list_s *nextNode;
} list_t;
/**
* struct builtin_s - A new struct type defining builtin commands.
* @name: The name of the builtin command.
* @function: A function pointer to the builtin command's function.
*/
typedef struct builtin_s
{
char *name;
int (*function)(char **argv, char **front);
} builtin_t;
/**
* struct alias_s - A new struct defining aliases.
* @name: The name of the alias.
* @number: The value of the alias.
* @next: A pointer to another struct alias_s.
*/
typedef struct alias_s
{
char *name;
char *number;
struct alias_s *nextNode;
} alias_t;
alias_t *aliases;
/* Global program name */
char *name;
/* Global history counter */
int hist;
ssize_t safeGetLine(char **lineptr, size_t *n, FILE *stream);
void *customRealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **customStrtok(char *line, char *delim);
char *getCommandLocation(char *command);
list_t *getPathDirectories(char *path);
int executeCommand(char **arguments, char **front);
void releaseList(list_t *initial);
char *intToString(int num);
void processLine(char **line, ssize_t read);
void substituteVariables(char **arguments, int *exe_ret);
char *getArguments(char *line, int *exe_ret);
int executeCommands(char **arguments, char **front, int *exe_ret);
int runCommands(char **arguments, char **front, int *exe_ret);
int handleCommands(int *exe_ret);
int validateCommands(char **arguments);
void releaseCommands(char **arguments, char **front);
char **replaceAliases(char **arguments);
int calculateStringLength(const char *s);
char *concatenateStrings(char *dest, const char *src);
char *concatenateStringsWithLength(char *dest, const char *src, size_t n);
char *copyString(char *dest, const char *src);
char *findFirstOccurrence(char *s, char c);
int calculateStringSpan(char *s, char *accept);
int compareStrings(char *s1, char *s2);
int compareStringsWithLength(const char *s1, const char *s2, size_t n);
int (*fetchBuiltinCommand(char *command))(char **arguments, char **front);
int exitShell(char **arguments, char **front);
int displayEnvironment(char **arguments,
char __attribute__((__unused__)) **front);
int setEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front);
int unsetEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front);
int changeDirectory(char **arguments,
char __attribute__((__unused__)) **front);
int handleAlias(char **arguments, char __attribute__((__unused__)) **front);
int showHelp(char **arguments, char __attribute__((__unused__)) **front);
char **duplicateEnvironment(void);
void releaseEnvironmentMemory(void);
char **searchEnvironment(const char *var);
int generateError(char **arguments, int err);
char *getErrorEnv(char **arguments);
char *getErrorMessage1(char **arguments);
char *getErrorMessage2Exit(char **arguments);
char *getErrorMessage2Cd(char **arguments);
char *getErrorMessage2Syntax(char **arguments);
char *getErrorMessage126(char **arguments);
char *getErrorMessage127(char **arguments);
alias_t *appendAlias(alias_t **initial, char *name, char *value);
void releaseAliasList(alias_t *initial);
list_t *appendNode(list_t **initial, char *directory);
void releaseList(list_t *initial);
void displayHelpAll(void);
void displayHelpAlias(void);
void displayHelpCd(void);
void displayHelpExit(void);
void printHelp(void);
void printHelpEnv(void);
void printSetenv(void);
void printUnsetenv(void);
void printHelpHistory(void);
int executeCmdFromFile(char *path, int *exec);
#endif /* _SHELL_H_ */
