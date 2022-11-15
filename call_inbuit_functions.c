#include "main.h"

/**
 * check_file_access - what it says
 * @filepath: parameter
 * Return: 1 on success
 */
int check_file_access(char *filepath)
{
	if (access(filepath, F_OK) != -1 && access(filepath, X_OK) != -1)
	{
		return (1);
	}
	return (0);
}
/**
 * call_inbuilt_func - what it says
 * @args: parameter
 * @env: env
 * @readbuf: read buffer
 * @count: error count
 * Return: 1 on success
 */
int call_inbuilt_func(char **args, char **env, char readbuf[], int *count)
{
	char *s;

	if (args[0] == NULL)
		return (1);
	if (_strcmp(args[0], "cd") == 0)
	{
		change_dir(args, env, count);
		return (1);
	}
	if (_strcmp(args[0], "exit") == 0)
	{
		call_exit(args, readbuf, count);
		return (1);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		if (args[3])
			illegal_no_args(count, "setenv");
		else if (args[1] && args[2])
			_setenv(args[1], args[2], 1);
		else
			illegal_no_args(count, "setenv");
		return (1);
	}
	if (_strcmp(args[0], "env") == 0 && !args[1])
	{
		printenv();
		return (1);
	}
	if (check_unsetenv(args, count) == 1)
		return (1);

	s = _which(args[0], environ, count);
	if (s == NULL)
		return (1);
	free(s);
	return (0);
}

/**
 * check_unsetenv  - checks commands to env
 * @args: arguments given
 * @count: error count
 *
 * Return: int
 */
int check_unsetenv(char **args, int *count)
{
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (args[2])
		{
			illegal_no_args(count, "unsetenv");
			return (1);
		}
		if (args[1])
		{
			_unsetenv(args[1]);
			return (1);
		}
		else
		{
			illegal_no_args(count, "unsetenv");
			return (1);
		}
	}
	return (0);
}

/**
 * printenv - prints current environment variables
 *
 * Return: void
 */
void printenv(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		_printf("%s\n", environ[i]);
		i++;
	}
}
