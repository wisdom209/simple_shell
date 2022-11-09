#include "main.h"
/**
 * change_dir - change directory
 * @args: parameter
 * @env: env
 */
void change_dir(char **args, char **env __attribute__((unused)))
{
	char *curr_dir = getcwd(NULL, 0);

	if (args[2])
	{
		printf("bash : too many arguments\n");
	}
	else if (!args[1] || strcmp(args[1], "~") == 0 ||
	strcmp(args[1], "--") == 0 || strcmp(args[1], "$HOME") == 0)
	{
		int a = chdir(_getenv("HOME"));

		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		set_directory(curr_dir);
	}
	else if (args[1] && strcmp(args[1], "-") == 0)
	{
		int a = chdir(_getenv("OLDPWD"));

		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		set_directory(curr_dir);
	}
	else if (args[1])
	{
		int a = chdir(args[1]);

		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		set_directory(curr_dir);
	}
}

/**
 * call_exit - exit
 * @args: parameter
 */
void call_exit(char **args)
{
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
}
/**
 * _getline - reads line from STDIN
 * Return: string
 */
char *_getline(void)
{
	int RL_BUFF_SIZE = 14096, buffsize = RL_BUFF_SIZE, position = 0, r;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;

	if (!buffer)
		return (NULL);
	while (1)
	{
		r = read(0, &c, 1);
		if (c == EOF || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else if (c == '\0')
			return (NULL);

		buffer[position] = c;
		position++;
		if (position >= buffsize)
		{
			buffsize += RL_BUFF_SIZE;
			buffer = realloc(buffer, buffsize);

			if (!buffer)
				return (NULL);
		}
	}
}

/**
 * set_directory - sets directory
 * @curr_dir: where to set old dir to
 */
void set_directory(char *curr_dir)
{
	_setenv("OLDPWD", curr_dir, 1);
	_setenv("PWD", getcwd(NULL, 0), 1);
}
