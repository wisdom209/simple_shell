#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

char **split_lines(char *cmd, char *delimiters);
char **copyenv(char **environ);
char *_getenv(char *search_path, char **env);
int isDelim(char c, char *delim);
int _setenv(char *env_name, char *env_value, int overwrite);

int main(int argc, char **argv, char **env)
{
	int i = 0, size = 0;
	char *s;
	printf("before setenv\n");
	while (environ[size])
	{
		printf("%s\n", environ[size]);
		size++;
	}
	printf("==========\n\n");
	printf("AfterSetenv\n");

	_setenv("hello", "www.hello.com", 1);

	size = 0;
	while (environ[size])
	{
		printf("%s\n", environ[size]);
		size++;
	}
	return (0);
}

int isDelim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/* TODO - fix potential malloc issues in this implementation */
char **split_lines(char *newstr, char *delimiter)
{
	if (newstr == NULL)
		return (NULL);
	char *str = strdup(newstr);
	strcat(str, delimiter); /* this line makes it work*/
	/* and i have no idea why??? */
	int str_size = strlen(str);
	int buffsize = str_size * str_size;
	char **tokens = malloc(sizeof(char) * buffsize);
	int indexer = -1;

	int i, j = 0, k = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (isDelim(str[i], delimiter))
		{
			continue;
		}

		indexer++;
		
		int e = 0;
		for (e = i; str[e] != '\0'; e++)
		{
			if (isDelim(str[e], delimiter))
			{
				break;
			}
			e++;
		}

		tokens[indexer] = malloc(sizeof(char) * (e - i));

		k = 0;
		for (j = i; str[j] != '\0'; j++)
		{
			if (isDelim(str[j], delimiter))
			{
				i = j - 1;
				break;
			}

			tokens[indexer][k] = str[j];
			k++;
		}
	}
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

/* TODO - modify in main code getenv to account for invalid paths */
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
		s = split_lines(a, "=")[0];

		if (strcmp(search_path, s) == 0)
		{
			found = 1;
			break;
		}
		i++;
	}

	/* gets the other path of PATH searched */
	if (found)
		s = split_lines(a, "=")[1];
	else
		s = NULL;

	return (s);
}

int _setenv(char *env_name, char *env_value, int overwrite)
{
	int i = 0, size = 0, highest = 0;

	if (env_name == NULL || env_value == NULL)
		return (-1);

	while (environ[size])
	{
		int a = strlen(environ[size]);
		if (a >= highest)
		{
			highest = a;
		}
		size++;
	}
	i = 0;
	while (env_name[i])
	{
		if (env_name[i] == '=')
		{
			return (-1);
		}
		i++;
	}
	if (overwrite == 0 && _getenv(env_name, environ))
		return (0);

	char **new_environ = malloc(sizeof(char) * (size + i + 4) * highest);

	i = 0;
	while (environ[i])
	{
		int env_size = strlen(environ[i]);
		new_environ[i] = malloc(sizeof(char) * env_size + 4);
		new_environ[i] = strdup(environ[i]);
		i++;
	}
	char *path_to_add = strdup(env_name);
	strcat(path_to_add, "=");
	strcat(path_to_add, env_value);
	new_environ[i] = strdup(path_to_add);
	new_environ[i + 1] = NULL;
	char **temp = environ;
	environ = new_environ;

	return (0);
}
