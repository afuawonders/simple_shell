#include "shell.h"
void displayHelpAll(void);
void displayHelpAlias(void);
void displayHelpCd(void);
void displayHelpExit(void);
void printHelp(void);
/**
* displayHelpAll - Displays all possible builtin shellby commands.
*/
void displayHelpAll(void)
{
char *prompt = "Shellby\nThese shell commands are defined internally.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "Type 'help' to see this list.\nType 'help name' to find ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "out more about the function 'name'.\n\n  alias   \t";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "unsetenv [VARIABLE]\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}
/**
* displayHelpAlias - Displays info on the shellby builtin command 'alias'
*/
void displayHelpAlias(void)
{
char *prompt = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "\n\talias: Prints a list of all aliases, one per line, in ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " the aliases name, name2, etc. one per line, in the ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " an alias for each NAME whose VALUE is given. If NAME ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "is already an alias, replace its value with VALUE.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}
/**
* displayHelpCd - Displays information on the shellby builtin command 'cd'.
*/
void displayHelpCd(void)
{
char *prompt = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "command is interpreted as cd $HOME. If the argument '-' is";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " given, the command is interpreted as cd $OLDPWD.\n\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "\tThe environment variables PWD and OLDPWD are updated ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "after a change of directory.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}
/**
* displayHelpExit - Displays information on the shellby builtin command 'exit'
*/
void displayHelpExit(void)
{
char *prompt = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "STATUS argument is the integer used to exit the shell.";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " If no argument is given, the command is interpreted as";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = " exit 0.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}
/**
* printHelp - Displays information on the shellby builtin command 'help'.
*/
void printHelp(void)
{
char *prompt = "help: help\n\tSee all possible Shellby builtin commands.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
prompt = "builtin command.\n";
write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}
