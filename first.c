#include "main.h"
/**
 * read_cmd - reads valid output from getline
 * Return: string
 */
char *read_cmd()
{
	size_t i = 0;
	char *buf = NULL;
	buf = _getline();

	if (buf == NULL)
	{
		kill(getpid(), 2);
	}

	return (buf);
}
/**
 * isDelim - delimiters
 * @c: parameter
 * @delim: parameter
 * Return: 1 if true
 */
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
/**
 * split_lines - split by delimiters
 * @newstr: parameter
 * @delimiters: parameter
 * Return: array of strings
 */
char **split_lines(char *newstr, char *delimiter)
{
	if (newstr == NULL)
		return (NULL);
	char *str = strdup(newstr);
	strcat(str, delimiter); /* this line makes it work*/
	/* and i have no idea why??? */
	int str_size = strlen(str);
	int buffsize = str_size * str_size;
	int token_size = 0;
	int t_index = 0;
	while (str[t_index] != '\0')
	{
		if (isDelim(str[token_size], delimiter))
		{
			token_size++;
		}
		t_index++;
	}
	char **tokens = malloc(sizeof(char) * token_size);
	int indexer = -1;

	int i, j = 0, k = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (isDelim(str[i], delimiter))
		{
			continue;
		}

		indexer++;
		tokens[indexer] = malloc(sizeof(char) * str_size);
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
	tokens[indexer + 1] = NULL;
	/* free(str);
	free(newstr); */
	return (tokens);
}
/**
 * exec_cmd - execute commands
 * @args: parameter
 * @env: env
 * Return: 0 on success
 */
int exec_cmd(char **args, char *env[])
{
	int a = call_inbuilt_func(args, env);
	char *location;
	char **env_two;

	if (a == 1)
		return (0);

	pid_t ch_pid = fork();

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
