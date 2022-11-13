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
	char **args;
	char *shell_name = argv[0];
	int count;

	_setenv("_", shell_name, 1);
	count = 1;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 3);
		cmd = read_cmd();
		if (!cmd)
			continue;
		args = _split(cmd, " ");
		exec_cmd(args, env, cmd, &count);
		free(args);

		if (isatty(STDIN_FILENO) == 0)
		{
			free(cmd);
			exit(0);
		}

		free(cmd);
	}

	return (0);
}
