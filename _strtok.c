#include "main.h"

size_t _strspn(const char *s, const char *accept);
char *_strpbrk(const char *s, const char *accept);
char *_strchr(char *str, char c);

/**
 * _strtok - works like strtok
 * @s: string to split
 * @delim: delimiter to split string by
 *
 * Return: split string
 */
char *_strtok(char *s, const char *delim)
{
	static char *olds;
	char *token;

	if (s == NULL)
		s = olds;

	/* Scan leading delimiters.  */
	s += _strspn(s, delim);
	if (*s == '\0')
	{
		olds = s;
		return (NULL);
	}

	/* Find the end of the token.  */
	token = s;
	s = _strpbrk(token, delim);
	if (s == NULL)
		/* This token finishes the string.  */
		olds = _strchr(token, '\0');
	else
	{
		/* Terminate the token and make OLDS point past it.  */
		*s = '\0';
		olds = s + 1;
	}
	return (token);
}

/**
 * _strspn - works like strspn
 * @s: string
 * @accept: accept
 *
 * Return: int
 */
size_t _strspn(const char *s, const char *accept)
{
	const char *p;
	const char *a;
	size_t count = 0;

	for (p = s; *p != '\0'; ++p)
	{
		for (a = accept; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return (count);
		++count;
	}
	return (count);
}
/**
 * _strpbrk - works like strpbrk
 * @s: string
 * @accept: accept
 *
 * Return: int
 */
char *_strpbrk(const char *s, const char *accept)
{
	while (*s != '\0')
	{
		const char *a = accept;

		while (*a != '\0')
			if (*a++ == *s)
				return ((char *)s);
		++s;
	}

	return (NULL);
}

/**
 * _strchr - works like strchr
 * @str: string
 * @c: accept
 *
 * Return: int
 */
char *_strchr(char *str, char c)
{
	char *p = str;

	do {
		if (*p == c)
			return (p);
	} while (*p++);
	return (NULL);
}
