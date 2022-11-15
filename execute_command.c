#include "main.h"

/**
 * exec_cmd - execute commands
 * @args: parameter
 * @env: env
 * @readbuf: input buffer
 * @count: error count
 *
 * Return: 0 on success
 */
int exec_cmd(char **args, char *env[], char readbuf[], int *count)
{
	int a = call_inbuilt_func(args, env, readbuf, count);
	char *location;
	pid_t ch_pid;

	if (a == 1)
		return (0);

	ch_pid = fork();

	if (ch_pid == 0)
	{
		a = 0;
		/* env_two = copyenv(environ); */
		location = _which(args[0], environ);

		execve(location, args, environ);

		exit(0);
	}
	else if (ch_pid > 0)
	{
		int status;

		wait(&status);

	}
	else
	{
		perror("bye\n");
		exit(1);
	}

	return (0);
}

