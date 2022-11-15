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
	_unsetenv(name);
	_strcpy(es, name);
	_strcat(es, "=");
	_strcat(es, value);

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
			return (-1);
		i++;
	}
	size = 0;
	while (environ[size])
		size++;

	set_location_of_var_to_unset(size, env_name, &location);

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

/**
 * set_location_of_var_to_unset - like it says
 * @size: environment variable array size
 * @env_name: environment variable to unset
 * @location: address of location variable to set
 *
 * Return: void
 */
void set_location_of_var_to_unset(int size, char *env_name, int *location)
{
	int i;

	for (i = 0; i < size; i++)
	{
		char *tmpa;
		char *a = _strdup(environ[i]);

		tmpa = a;
		a = _strtok(a, "=");
		if (_strcmp(a, env_name) == 0)
		{
			free(tmpa);
			*location = i;
			break;
		}
		free(tmpa);
	}
}

/**
 * _getenv - getenv
 * @search_path: search path
 *
 * Return: char *
 */
char *_getenv(char *search_path)
{
	int i = 0;
	char *result;

	while (environ[i])
	{
		char *tmp_a;
		char *a = _strdup(environ[i]);
		tmp_a = a;
		a = _strtok(a, "=");

		if (_strcmp(a, search_path) == 0)
		{
			a = _strtok(NULL, "=");
			result = strdup(a);
			free(tmp_a);
			return (result);
		}
		free(tmp_a);
		i++;
	}

	return (NULL);
}
