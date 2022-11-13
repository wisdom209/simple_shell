#include "main.h"
#include "errno.h"
/**
 * _setenv - set environment
 * @name: parameter
 * @value: parameter
 * @overwrite: parameter
 * Return: 0/-1
 */
int _setenv(char *name, char *value, int overwrite)
{
	char es[1024];
	char *env_name_check;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
		value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	env_name_check = _getenv(name);
	if (env_name_check != NULL && overwrite == 0)
	{
		free(env_name_check);
		return (0);
	}
	free(env_name_check);

	_unsetenv(name); /* Remove all occurrences */

	/* es = malloc(strlen(name) + strlen(value) + 2); */
	/* +2 for '=' and null terminator */
	/* if (es == NULL)
		return (-1); */

	strcpy(es, name);
	strcat(es, "=");
	strcat(es, value);

	return (setenv(name, value, 1));
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
	char *env_name_check;

	if (env_name == NULL)
		return (-1);

	env_name_check = _getenv(env_name);
	if (!env_name_check)
	{
		free(env_name_check);
		return (0);
	}
	free(env_name_check);
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
		char *tmpa;
		char *a = strdup(environ[i]);

		tmpa = a;
		a = _strtok(a, "=");

		if (strcmp(a, env_name) == 0)
		{
			free(tmpa);
			location = i;
			break;
		}
		free(tmpa);
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
