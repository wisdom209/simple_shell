#include "main.h"
/**
 * change_dir - change directory
 * @args: parameter
 * @env: env
 */
void change_dir(char **args, char **env)
{
	/* TODO - FIX EMPTY ARG TO CD */
	curr_dir = getcwd(NULL, 0);
	if (args[2])
	{
		printf("bash : too many arguments\n");
		return;
	}
	else if (!args[1] || strcmp(args[1], "~") == 0 || strcmp(args[1], "--") == 0 || strcmp(args[1], "$HOME") == 0)
	{
		int a = chdir(home);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
	else if (args[1] && strcmp(args[1], "-") == 0)
	{
		int a = chdir(old_dir);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
	else if (args[1])
	{
		int a = chdir(args[1]);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
}

/**
 * call_exit - exit
 * @args: parameter
 */
void call_exit(char **args)
{
	/* TODO - get the implementations of atoi*/

	if (!args[1])
	{
		exit(0);
	}
	if (args[2])
	{
		printf("bash: illegal number of arguments");
	}

	if (args[1])
	{
		if (strlen(args[1]) == 1 && args[1][0] == '0')
		{
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
			if (a > INT_MAX || strlen(args[1]) > 10)
			{
				printf("bash : illegal number\n");
				return;
			}
			exit(a % 256);
		}

		return;
	}

	return;
}
/**
 * _getline - reads line from STDIN
 * Return: string
 */
char *_getline(void)
{
	int RL_BUFF_SIZE = 1024;
	int buffsize = RL_BUFF_SIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;
	int r;

	if (!buffer)
	{
		return (NULL);
	}

	while (1)
	{
		r = read(0, &c, 1);
		if (c == EOF || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return buffer;
		}
		else if (c == '\0')
		{
			return (NULL);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= buffsize)
		{
			buffsize += RL_BUFF_SIZE;
			buffer = realloc(buffer, buffsize);

			if (!buffer)
			{
				return (NULL);
			}
		}
	}
}

