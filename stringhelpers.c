#include "main.h"
/**
 * _strcat - appends
 * @dest: first
 * @src: second
 * Return: string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j;

	while (dest[i] != '\0')
		i++;
	for (j = 0; src[j] != '\0'; j++, i++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compare
 * @s1: first
 * @s2: second
 * Return: number
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	for (; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strlen - string length
 * @s: parameter
 * Return: int
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strdup - duplicates strings
 * @src: source
 * Return: string
*/
char *_strdup(char *src)
{
	int src_size;
	static char *dest;
	char *dest_pointer;

	/* Allocate memory for destlicate */
	src_size = strlen(src);
	dest = (char *)malloc(src_size + 1);
	if (!dest)
		return (NULL);

	/* Copy string */
	dest_pointer = dest;
	while (*src)
		*dest_pointer++ = *src++;
	*dest_pointer = '\0';

	return (dest);
}

char *_strtok(char *str, const char *delim)
{
	static char *s_str = NULL; /* var to store last address */
	char *p;

	if (delim == NULL || (str == NULL && s_str == NULL))
	{
		return NULL;
	}

	if (str == NULL)
	{
		str = s_str;
	}

	/* if delim is not contained in str, return str */
	if ((p = strstr(str, delim)) == NULL)
	{
		s_str = NULL;
		return str;
	}

	/*
	 * check for consecutive delimiters
	 * if first char is delim, return delim
	 */
	if (str[0] == delim[0])
	{
		s_str++;
		return (char *)delim;
	}

	/* terminate the string */
	*p = '\0';

	/* save the rest of the string */
	if ((p + 1) != NULL)
	{
		s_str = (p + 1);
	}
	else
	{
		s_str = NULL;
	}

	return str;
}
