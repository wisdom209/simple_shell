#include "main.h"
#include <signal.h>
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
		exit(0);
	}

	return (buf);
}

/**
 * _getline - reads line from STDIN
 * Return: string
 */
char *_getline(void)
{
	int RL_BUFF_SIZE = 14096, buffsize = RL_BUFF_SIZE, position = 0, r;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;

	if (!buffer)
		return (NULL);
	while (1)
	{
		r = read(0, &c, 1);
		if (c == EOF || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else if (c == '\0')
			return (NULL);

		buffer[position] = c;
		position++;
		if (position >= buffsize)
		{
			buffsize += RL_BUFF_SIZE;
			buffer = realloc(buffer, buffsize);

			if (!buffer)
				return (NULL);
		}
	}
}
