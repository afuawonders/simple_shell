#include "shell.h"

void printHelpEnv(void);
void printSetenv(void);
void printUnsetenv(void);
void printHelpHistory(void);

/**
 * printHelpEnv - Displays information on the shellby builtin command 'env'.
 */
void printHelpEnv(void)
{
	char *prompt = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}

/**
 * printSetenv - Displays information on the shellby builtin command 'setenv'.
 */
void printSetenv(void)
{
	char *prompt = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
	prompt = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
	prompt = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}

/**
 * printUnsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void printUnsetenv(void)
{
	char *prompt = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
	prompt = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
	prompt = "message to stderr.\n";
	write(STDOUT_FILENO, prompt, calculateStringLength(prompt));
}

