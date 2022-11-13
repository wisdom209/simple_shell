#include "main.h"
/**
 * _strtok - works like strtok
 * @str: string to split
 * @delim: delimiter to split string by
 *
 * Return: split string
 */
char *_strtok(char *str, const char *delim)
{
	static char *s_str;
	char *p;

	if (delim == NULL || (str == NULL && s_str == NULL))
		return (NULL);

	if (str == NULL)
		str = s_str;

	p = strstr(str, delim);
	if (p == NULL)
	{
		s_str = NULL;
		return (str);
	}

	if (str[0] == delim[0])
	{
		s_str++;
		return ((char *)delim);
	}

	*p = '\0';
	if ((p + 1) != NULL)
		s_str = (p + 1);
	else
		s_str = NULL;

	return (str);
}
