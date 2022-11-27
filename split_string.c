#include "main.h"
#include <ctype.h>

/**
 * _split - split a string into an array
 * @str: string to split
 * @delimiter: delimiter to split by
 *
 * Return: string array
 */

char **_split(char *str, char *delimiter)
{
	int length = 0;
	int capacity = 16;
	char *token;
	char **tokens = malloc(capacity * sizeof(char *));

	if (!tokens)
	{
		exit(1);
	}

	token = _strtok(str, delimiter);

	while (token != NULL)
	{
		tokens[length] = token;
		length++;

		if (length >= capacity)
		{
			int old_cap = capacity;

			capacity = (int)(capacity * 1.5);

			tokens = _realloc(tokens, old_cap * sizeof(char *),
							  capacity * sizeof(char *));

			if (!tokens)
			{
				exit(1);
			}
		}

		token = _strtok(NULL, delimiter);
	}

	tokens[length] = NULL;
	return (tokens);
}

/**
 * isDelim - checks if a char is delim
 * @c: char to check
 * @delim: delim to chec
 *
 * Return: int
 */
int isDelim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}

	return (0);
}
