#include "main.h"

char *old_dir;
char *curr_dir;
char *home;
/**
 * main - main function
 * @argc: argument count
 * @argv: array of argument strings
 * @env: environment variables
 * Return: 0 on success
 */
int main(int argc __attribute_maybe_unused__, char **argv __attribute_maybe_unused__, char **env __attribute_maybe_unused__)
{
	/* home = getenv("HOME", env); */

	char *cmd;
	char **args;

	while (1)
	{
		home = getenv("HOME");
		write(STDIN_FILENO, "$ ", 3);
		cmd = read_cmd();
		args = split_lines(cmd, " \t\r\n");
		exec_cmd(args, env);
		free(args);
		free(cmd);
	}

	return (0);
}

/* TODO - incorrect commands more than two letters gives malloc error */
/*
char *_getenv(char *search_path, char **env)
{
	int i = 0, size = 0;
	char *s = NULL;
	char *a = NULL;
	int found = 0;
	if (search_path == NULL)
		return (NULL);

	while (env[i])
	{
		a = strdup(env[i]);
		char **stri = split_lines(a, "=");
		s = stri[0];

		if (strcmp(search_path, s) == 0)
		{
			found = 1;
			break;
		}
		free(stri[0]);
		free(stri[1]);
		free(stri);
		i++;
	}


	if (found == 1)
	{
		char **str = split_lines(a, "=");
		s = str[1];
		free(str[0]);
		free(str[1]);
		free(str);
	}
	else
		s = NULL;
	free(a);

	return (s);
}
*/

/* char **copyenv(char **environ)
{
	int size = 0;
	while (environ[size])
	{
		size++;
	}

	char **new_environ = malloc(sizeof(char) * size * 1024);

	if (!new_environ)
	{
		return (NULL);
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		new_environ[i] = malloc(sizeof(char) * strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			for (int j = i - 1; i >= 0; i--)
			{
				free(new_environ[i]);
			}
			free(new_environ);
		}
		strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}
 */
