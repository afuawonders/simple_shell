#include "shell.h"
/**
 * getErrorEnv - Creates an error message for displayEnvironment errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *getErrorEnv(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = intToString(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = calculateStringLength(name) + calculateStringLength(hist_str)
	+ calculateStringLength(args[0]) + 45;
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
	concatenateStrings(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * getErrorMessage1 - Creates an error message for handleAlias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *getErrorMessage1(char **args)
{
	char *error;
	int len;

	len = calculateStringLength(name) + calculateStringLength(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	copyString(error, "alias: ");
	concatenateStrings(error, args[0]);
	concatenateStrings(error, " not found\n");

	return (error);
}

/**
 * getErrorMessage2Exit - Creates an error message for exitShell errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *getErrorMessage2Exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = intToString(hist);
	if (!hist_str)
		return (NULL);

	len = calculateStringLength(name) + calculateStringLength(hist_str)
	 + calculateStringLength(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copyString(error, name);
	concatenateStrings(error, ": ");
	concatenateStrings(error, hist_str);
	concatenateStrings(error, ": exit: Illegal number: ");
	concatenateStrings(error, args[0]);
	concatenateStrings(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * getErrorMessage2Cd - Creates an error message for changeDirectory errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *getErrorMessage2Cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = intToString(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		concatenateStrings(error, ": cd: Illegal option ");
	else
		concatenateStrings(error, ": cd: can't cd to ");
	concatenateStrings(error, args[0]);
	concatenateStrings(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * getErrorMessage2Syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *getErrorMessage2Syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = intToString(hist);
	if (!hist_str)
		return (NULL);

	len = calculateStringLength(name) + calculateStringLength(hist_str) +
	calculateStringLength(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copyString(error, name);
	concatenateStrings(error, ": ");
	concatenateStrings(error, hist_str);
	concatenateStrings(error, ": Syntax error: \"");
	concatenateStrings(error, args[0]);
	concatenateStrings(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
