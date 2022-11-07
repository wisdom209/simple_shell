#include "main.h"

/*
 * check_location - check location
 * @args: arguments
 *
 * Return: int
 */
int check_location(char **args, char *delimiter)
{
	char *location = split_lines(args[0], delimiter)[0];
	char *a = _which(location, environ);

	if (a == NULL)
		return (-1);

	return (1);
}
