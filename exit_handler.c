#include "main.h"

/**
 * call_exit - exit
 * @args: parameter
 * @readbuf: read buffer
 */
void call_exit(char **args, char readbuf[])
{
	if (!args[1])
	{
		free_arguments_and_buffer(args, readbuf);
		exit(0);
	}
	if (args[2])
		printf("bash: illegal number of arguments");
	if (args[1])
	{
		if (_strlen(args[1]) == 1 && args[1][0] == '0')
		{
			free_arguments_and_buffer(args, readbuf);
			exit(0);
		}
		else if (args[1][0] == '-')
		{
			printf("bash : illegal number\n");
			return;
		}
		else
		{
			int a = atoi(args[1]);

			if (a == 0)
			{
				printf("bash : illegal number\n");
				return;
			}
			if (a > INT_MAX || _strlen(args[1]) > 10)
			{
				printf("bash : illegal number\n");
				return;
			}
			free_arguments_and_buffer(args, readbuf);
			exit(a % 256);
		}
		return;
	}
}
