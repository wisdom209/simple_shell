#include "main.h"
/**
 * read_cmd - reads valid output from getline
 * Return: string
 */
char *read_cmd()
{
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
 * @delimiter: parameter
 * Return: array of strings
 */
char **split_lines(char *newstr, char *delimiter)
{
	char *str;
	char **tokens;
	int token_size = 0, t_index = 0, strsize, indexer = -1, i = 0, j = 0, k = 0;

	if (newstr == NULL)
		return (NULL);
	str = malloc(sizeof(char) * strlen(newstr) + 2);
	if (str == NULL)
		return (NULL);
	strcpy(str, "");
	strcat(str, newstr);
	strcat(str, delimiter);
	strsize = strlen(str);
	token_size = check_token_length(str, delimiter, t_index, token_size);
	tokens = malloc(sizeof(char *) * token_size);
	if (tokens == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isDelim(str[i], delimiter))
			continue;

		indexer++;
		tokens[indexer] = calloc(1, sizeof(char) * strsize);
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
	pid_t ch_pid;

	if (a == 1)
		return (0);

	ch_pid = fork();

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

/**
 * check_token_length - expected num of tokens ??
 * @str: string to break
 * @delimiter: delim
 * @t_index: token index
 * @token_size: expected size
 *
 * Return: int
 */
int check_token_length(char *str, char *delimiter, int t_index, int token_size)
{

	while (str[t_index] != '\0')
	{
		if (isDelim(str[token_size], delimiter))
		{
			token_size++;
		}
		t_index++;
	}
	return (token_size);
}
