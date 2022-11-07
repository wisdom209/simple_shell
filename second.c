#include "main.h"
/**
 * _which - searches for command in env
 * @search_var: parameter
 * @env: env
 * Return: path string
 */
char *_which(char *search_var, char **env)
{
	int i = 0, size = 0;
	char *s;
	char **paths;
	/* env = copyenv(env); */

	if (search_var[0] == '/')
	{
		if (check_file_access(search_var) != 1)
		{
			printf("%s: command not found\n", search_var);
			return (NULL);
		}
		return (search_var);
	}
	else
	{
		/* s = getenv("PATH", env); */
		s = getenv("PATH");

		paths = split_lines(s, ":");

		char *strA = malloc(sizeof(search_var) * 10);
		strcat(strA, "/");
		strcat(strA, search_var);

		i = 0;
		while (paths[i])
		{
			char *checkstr = strcat(strdup(paths[i]), strA);

			if (check_file_access(checkstr) == 1)
			{
				/* free(strA); */
				return (checkstr);
			}

			/* free(checkstr); */
			i++;
		}
	}
	printf("%s: command not found\n", search_var);

	return (NULL);
}
/**
 * check_file_access - what it says
 * @filepath: parameter
 * Return: 1 on success
 */
int check_file_access(char *filepath)
{
	if (access(filepath, F_OK) != -1 && access(filepath, X_OK) != -1)
	{
		return (1);
	}
	return (0);
}
/**
 * call_inbuilt_func - what it says
 * @args: parameter
 * @env: env
 * Return: 1 on success
 */
int call_inbuilt_func(char **args, char **env)
{
	if (strcmp(args[0], "cd") == 0)
	{
		change_dir(args, env);
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		call_exit(args);
		return (1);
	}
	if (strcmp(args[0], "setenv") == 0)
	{
		if (args[3])
		{
			printf("invalid number of args\n");
			return (1);
		}

		if (args[1] && args[2])
			_setenv(args[1], args[2], 0);
		else
			printf("invalid input\n");

		return (1);
	}
	if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[2])
		{
			printf("invalid number of args\n");
			return (1);
		}

		if (args[1] )
			_unsetenv(args[1]);
		else
			printf("invalid input\n");

		return (1);
	}
	return (0);
}
