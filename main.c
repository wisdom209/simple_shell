#include "main.h"
#include "errno.h"

void handle_non_interactive(int shell_interaction,
							int argc, char *cmd, char **args, char **env, int *count);

/**
 * main - main function
 * @argc: argument count
 * @argv: array of argument strings
 * @env: environment variables
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	char *cmd = NULL;
	char **args = NULL;
	char *shell_name = argv[0];
	int count;
	int shell_interaction;

	_setenv("_", shell_name, 1);
	count = 1;

	shell_interaction = isatty(STDIN_FILENO);

	handle_non_interactive(shell_interaction, argc, cmd, args, env, &count);

	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "$ ", 3);

		cmd = read_cmd();

		args = _split(cmd, " \t\f\v\a");

		exec_cmd(args, env, cmd, &count);
		free(args);
		free(cmd);
	}

	return (0);
}

void handle_non_interactive(int shell_interaction,
							int argc, char *cmd, char **args, char **env, int *count)
{
	if (shell_interaction == 0 && argc == 1) /* if non-interactive */
	{
		int exit_code = 0;
		char *exitchar;

		exitchar = _getenv("err_code");

		if (exitchar != NULL)
		{
			exit_code = atoi(exitchar);
			free(exitchar);
		}

		while ((cmd = read_cmd()) != NULL) /* grabs input */
		{
			args = _split(cmd, " \t\n\a\r\f\v");

			exec_cmd(args, env, cmd, count);

			free(args);
			free(cmd);
		}

		exit(exit_code);
	}
}
