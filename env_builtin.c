#include "shell.h"

char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *var);

/**
 * copy_environment - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_environment(void)
{
	char **new_env;
	size_t env_size;
	int i;

	for (env_size = 0; environ[env_size]; env_size++)
	{
		new_env = malloc(sizeof(char *) * (env_size + 1));
		if (!new_env)
			return (NULL);
	}

	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[i], environ[i]);
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * free_environment - Frees the environment copy.
 */
void free_environment(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * get_environment_variable - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_environment_variable(const char *var)
{
	int i, var_len;

	var_len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], var_len) == 0)
			return (&environ[i]);
	}
	return (NULL);
}
