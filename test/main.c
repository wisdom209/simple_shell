#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

char **split_lines(char *cmd, char *delimiters);
char **copyenv(char **environ);

int main(int argc, char **argv, char **env)
{
	int i = 0, size = 0;
	char *s;
	while (env[size])
		size++;

	char **newenv = copyenv(env);

	while (newenv[i])
	{
		printf("%s\n", newenv[i]);
		i++;
	}
	/*
		while (env[i])
		{

			s = strtok(env[i], "=");
			if (strcmp("PATH", s) == 0)
				break;
			i++;
		}
		s = strtok(NULL, "=");

		char **paths = split_lines(s, ":");

		i = 0;
		while (paths[i])
		{

			char *s = strcat(paths[i], "/code");
			if (access(s, F_OK) != -1 && access(s, X_OK) != -1)
			{
				printf("%s\n", paths[i]);
				break;
			}

			i++;
		} */

	return (0);
}

char **split_lines(char *cmd, char *delimiters)
{

	char **tokens = malloc(sizeof(cmd) * 2048);
	char *token = strtok(cmd, delimiters);
	int pos = 0;

	if (!tokens)
		exit(1);

	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, delimiters);
	}
	tokens[pos] = NULL;

	return (tokens);
}

char **copyenv(char **environ)
{
	int size = 0;
	while (environ[size])
	{
		size++;
	}

	char **new_environ = malloc(sizeof(char) * size + 1);

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
