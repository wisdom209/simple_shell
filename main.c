#include "main.h"
int main(int argc, char **argv, char **env)
{
	/* home = getenv("HOME", env); */
	home = getenv("HOME");

	while (1)
	{
		write(STDIN_FILENO, "$ ", 3);
		char *cmd = read_cmd();
		char **args = split_lines(cmd, " \t\r\n");
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

