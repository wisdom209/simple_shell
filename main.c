#include "main.h"

char *shell_name;
/**
 * main - main function
 * @argc: argument count
 * @argv: array of argument strings
 * @env: environment variables
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	char *cmd;
	char **args;

	if (_getenv("OLDPWD") == NULL)
		_setenv("OLDPWD", _getenv("HOME"), 1);

	shell_name = argv[0];
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 3);
		cmd = read_cmd();
		if (!cmd)
			continue;
		args = split_lines(cmd, " \t\r\n");
		exec_cmd(args, env);
		free(args);
		free(cmd);
	}

	return (0);
}

/* TODO - incorrect commands more than two letters gives malloc error */
/**
 * _getenv - getenv
 * @search_path: search path
 *
 * Return: char *
 */
char *_getenv(char *search_path)
{
	int i = 0;
	char *s = NULL;
	char *a = NULL;
	char **stri = NULL;
	int found = 0;

	while (environ[i])
	{
		a = strdup(environ[i]);
		stri = split_lines(a, "=");
		s = stri[0];

		if (strcmp(search_path, s) == 0)
		{
			found = 1;
			break;
		}
		i++;
	}

	if (found == 1)
	{
		char **str = split_lines(a, "=");

		s = str[1];
	}
	else
		return (NULL);

	return (s);
}
