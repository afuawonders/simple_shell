#include "shell.h"

int displayEnvironment(char **arguments,
char __attribute__((__unused__)) **front);
int setEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front);
int unsetEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front);

/**
 * displayEnvironment - Prints the current environment.
 * @arguments: An array of arguments passed to the shell.
 * @__attribute__: A function that accepts values
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int displayEnvironment(char **arguments,
char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index],
		calculateStringLength(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)arguments;
	return (0);
}

/**
 * setEnvironmentVariable - Changes or adds an environ var to the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the name of the new or existing PATH variable.
 * arguments[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int setEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;
	if (!arguments[0] || !arguments[1])
		return (generateError(arguments, -1));
	new_value = malloc(calculateStringLength(arguments[0]) + 1 +
	calculateStringLength(arguments[1]) + 1);
	if (!new_value)
		return (generateError(arguments, -1));
	copyString(new_value, arguments[0]);
	concatenateStrings(new_value, "=");
	concatenateStrings(new_value, arguments[1]);
	env_var = searchEnvironment(arguments[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_environ = malloc(sizeof(char *) * (size + 2));

	if (!new_environ)
	{
		free(new_value);
		return (generateError(arguments, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];
	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;
	return (0);
}


/**
 * unsetEnvironmentVariable - Deletes an environmental variable from the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unsetEnvironmentVariable(char **arguments,
char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!arguments[0])
		return (generateError(arguments, -1));
	env_var = searchEnvironment(arguments[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (generateError(arguments, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

