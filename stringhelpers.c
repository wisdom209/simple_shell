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
	src_size = _strlen(src);
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

/**
 * _strcpy - string copy
 * @destination: destination string
 * @source: source string
 *
 * Return: destination copy
 */
char *_strcpy(char *destination, char *source)
{
	char *ptr;

	if (destination == NULL)
		return (NULL);

	ptr = destination;

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return (ptr);
}
