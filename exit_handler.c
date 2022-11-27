#include "main.h"
#include <ctype.h>
#include <errno.h>
void handle_specified_exit(char **args, int *count, char readbuf[]);

/**
 * call_exit - exit
 * @args: parameter
 * @readbuf: read buffer
 * @count: error count
 */
void call_exit(char **args, char readbuf[], int *count)
{
	if (!args[1])
	{
		free_arguments_and_buffer(args, readbuf);
		if (errno == 25)
			exit(0);
		exit(errno);
	}
	if (args[1])
	{
		if (_strlen(args[1]) == 1 && args[1][0] == '0')
		{
			free_arguments_and_buffer(args, readbuf);
			exit(errno);
		}
		else if (args[1][0] == '-')
		{
			char *shell_name = _getenv("_");

			illegal_no_err(count, shell_name, args[1]);
			free(shell_name);
			if (isatty(STDIN_FILENO) == 0)
			{
				free_arguments_and_buffer(args, readbuf);
				exit(2);
			}
			return;
		}
		else
		{
			handle_specified_exit(args, count, readbuf);
		}
		return;
	}
}

/**
 * handle_exit_num_errors - handle errors
 * @a: num to check
 * @count: error count
 * @args: current args
 *
 * Return: int
 */
int handle_exit_num_errors(int a, int *count, char **args)
{
	if (_isDigit(args[1]) == 0)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	if (a == 0)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	if (a > INT_MAX || _strlen(args[1]) > 10)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	return (0);
}

/**
 * _isDigit - checks if string is digit
 * @s: string to check
 *
 * Return: int
 */
int _isDigit(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * handle_specified_exit - handles exit nums specified
 * @args: argument tokens
 * @readbuf: read buffer
 * @count: error count
 *
 * Return: void
 */
void handle_specified_exit(char **args, int *count, char readbuf[])
{
	int a = atoi(args[1]);

	if (a == 0 && _strcmp(args[1], "0") != 0)
	{
		handle_exit_num_errors(a, count, args);
		if (isatty(STDIN_FILENO) == 0)
		{
			free_arguments_and_buffer(args, readbuf);
			exit(2);
		}
		return;
	}
	if (handle_exit_num_errors(a, count, args) == 1)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			free_arguments_and_buffer(args, readbuf);
			exit(2);
		}
		return;
	}
	free_arguments_and_buffer(args, readbuf);
	exit(a % 256);
}
