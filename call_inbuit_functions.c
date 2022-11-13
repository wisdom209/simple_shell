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
 * Return: 1 on success
 */
int call_inbuilt_func(char **args, char **env, char readbuf[])
{
	char *s;

	if (args[0] == NULL)
		return (1);
	if (_strcmp(args[0], "cd") == 0)
	{
		change_dir(args, env);
		return (1);
	}
	if (_strcmp(args[0], "exit") == 0)
	{
		call_exit(args, readbuf);
		return (1);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		char *shell_name = _getenv("_");

		if (args[3])
			_printf("%s: illegal number of arguments\n", shell_name);
		else if (args[1] && args[2])
			_setenv(args[1], args[2], 0);
		else
			_printf("%s: illegal number of arguments\n", shell_name);
		free(shell_name);
		return (1);
	}
	if (check_unsetenv(args) == 1)
		return (1);

	s = _which(args[0], environ);

	if (s == NULL)
		return (1);
	free(s);
	return (0);
}

/**
 * check_unsetenv  - checks commands to env
 * @args: arguments given
 *
 * Return: int
 */
int check_unsetenv(char **args)
{
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (args[2])
		{
			printf("invalid number of args\n");
			return (1);
		}
		if (args[1])
			_unsetenv(args[1]);
		else
			printf("invalid input\n");
		return (1);
	}
	return (0);
}
