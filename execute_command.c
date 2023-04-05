#include "main.h"
#include <errno.h>

/**
 * exec_cmd - execute commands
 * @args: parameter
 * @env: env
 * @readbuf: input buffer
 * @count: error count
 * @glbs: global vars
 *
 * Return: 0 on success
 */
int exec_cmd(char **args, char *env[], char readbuf[],
			 int *count, t_globs *glbs)
{
	int a = call_inbuilt_func(args, env, readbuf, count, glbs);
	int status;
	char *location;
	pid_t ch_pid;

	if (a == 1)
		return (0);

	ch_pid = fork();

	if (ch_pid == 0)
	{
		a = 0;

		location = _which(args[0], environ, count, glbs);
		execve(location, args, environ);
		exit(-1);
	}
	else if (ch_pid > 0)
	{
		wait(&status);
		if (status == 0)
		{
			errno = 0;
			_setenv("err_code", "0", 1);
		}
		if (status == 512)
		{
			errno = 2;
			_setenv("err_code", "2", 1);
		}
		if (status == 65280)
		{
			errno = 127;
			_setenv("err_code", "127", 1);
		}
	}
	return (status);
}
