#include "main.h"
/* implement set env - malloc issues yet to */
/* implement set env - malloc issues yet to */
/**
 * _setenv - set environment
 * @env_name: parameter
 * @env_value: parameter
 * @overwrite: parameter
 * Return: 0/-1
 */
int _setenv(char *env_name, char *env_value, int overwrite)
{
	char *path_to_add = env_name;

	if (env_name == NULL || env_value == NULL)
		return (-1);

	/* if (overwrite == 0 && getenv(env_name, environ))
		return (0); */
	if (overwrite == 0 && getenv(env_name))
		return (0);
	

	strcat(path_to_add, "=");
	strcat(path_to_add, env_value);

	

	putenv(path_to_add);

	return (0);
}

/* unset env... does not use malloc, should not need to be freed */
/**
 * _unsetenv - set environment
 * @env_name: parameter
 * Return: 0/-1
 */
int _unsetenv(char *env_name)
{
	int i = 0, size = 0, location = 0;

	if (env_name == NULL)
		return (-1);
	/*
		if (!getenv(env_name, environ))
			return (0); */

	if (!getenv(env_name))
		return (0);

	while (env_name[i])
	{
		if (env_name[i] == '=')
		{
			return (-1);
		}
		i++;
	}

	size = 0;
	while (environ[size])
		size++;

	for (i = 0; i < size; i++)
	{
		char *a = split_lines(environ[i], "=")[0];

		if (strcmp(a, env_name) == 0)
		{
			location = i;
			break;
		}
	}

	for (i = location; i < size; i++)
	{
		if (environ[i + 1] == NULL)
		{
			environ[i] = NULL;
			break;
		}
		environ[i] = environ[i + 1];
	}
	return (0);
}
