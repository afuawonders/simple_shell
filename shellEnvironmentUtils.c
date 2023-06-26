#include "shell.h"

char **duplicateEnvironment(void);
void releaseEnvironmentMemory(void);
char **searchEnvironment(const char *var);

/**
 * duplicateEnvironment - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **duplicateEnvironment(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(calculateStringLength(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		copyString(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * releaseEnvironmentMemory - Frees the the environment copy.
 */
void releaseEnvironmentMemory(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * searchEnvironment - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **searchEnvironment(const char *var)
{
	int index, len;

	len = calculateStringLength(var);
	for (index = 0; environ[index]; index++)
	{
		if (compareStringsWithLength(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}

