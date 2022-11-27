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
		return (NULL);
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
	char c = 0;

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
		{
			free(buffer);
			return (NULL);
		}

		buffer[position] = c;
		position++;
		if (position >= buffsize)
		{
			buffer = _realloc(buffer, buffsize, buffsize + RL_BUFF_SIZE);
			buffsize += RL_BUFF_SIZE;

			if (!buffer)
				return (NULL);
		}
	}
}

/**
 * _realloc - reallocates space
 * @ptr: old block
 * @old_size: old size
 * @new_size: new size
 *
 * Return: pointer to new block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i = 0;
	char *newPtr;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		newPtr = malloc(new_size);
		if (!newPtr)
			return (NULL);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size > old_size && (ptr != NULL))
	{
		newPtr = malloc(new_size);

		if (!newPtr)
			return (NULL);

		for (i = 0; i < old_size; i++)
		{
			newPtr[i] = ((char *)ptr)[i];
		}

		free(ptr);
	}
	return (newPtr);
}
