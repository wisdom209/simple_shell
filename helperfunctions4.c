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
	char *es;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
		value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (_getenv(name) != NULL && overwrite == 0)
		return (0);

	_unsetenv(name); /* Remove all occurrences */

	es = malloc(strlen(name) + strlen(value) + 2);
	/* +2 for '=' and null terminator */
	if (es == NULL)
		return (-1);

	strcpy(es, name);
	strcat(es, "=");
	strcat(es, value);

	return ((putenv(es) != 0) ? -1 : 0);
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
	if (!_getenv(env_name))
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
