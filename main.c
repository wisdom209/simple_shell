#include "main.h"

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
	int i;
	char **args;
	char *shell_name = argv[0];
	char *oldpwd = _getenv("OLDPWD");
	char *home = _getenv("HOME");

	if (oldpwd == NULL)
		_setenv("OLDPWD", home, 1);
	_setenv("shell_name", shell_name, 1);
	free(home);
	free(oldpwd);

	while (1)
	{
		i = 0;
		write(STDOUT_FILENO, "$ ", 3);
		cmd = read_cmd();
		if (!cmd)
			continue;
		args = _split(cmd, " ");
		exec_cmd(args, env, cmd);
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
	char *a;
	char *s = getenv(search_path);
	if (s != NULL)
		a = strdup(s);
	else
		a = NULL;

	return (a);
}
