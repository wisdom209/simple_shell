#include "main.h"
/**
 * _which - searches for command in env
 * @search_var: parameter
 * @env: env
 * Return: path string
 */
char *_which(char *search_var, char **env __attribute__((unused)))
{
	int i = 0;
	char *s = NULL, *strA = NULL, *shell_name = _getenv("_");
	char **paths;
	char *search_ret = _strdup(search_var);

	if (search_var[0] == '/' && (search_abs_path(shell_name, search_var) != NULL))
		return (search_ret);
	free(search_ret);
	s = _getenv("PATH"), strA = malloc(sizeof(search_var) * 10);
	paths = _split(s, ":");
	free(s);
	if (strA == NULL)
	{
		free_malloc_strings(2, paths, shell_name);
		return (NULL);
	}
	concat_malloc_str(strA, "/", search_var);
	while (paths[i])
	{
		char *checkstr = malloc(1024);

		if (checkstr == NULL)
		{
			free_malloc_strings(2, paths, shell_name);
			return (NULL);
		}
		concat_malloc_str(checkstr, paths[i], strA);
		if (check_file_access(checkstr) == 1)
		{
			free_malloc_strings(3, paths, strA, shell_name);
			return (checkstr);
		}
		else
			free(checkstr);
		i++;
	}
	_printf("%s: ", shell_name);
	perror(NULL);
	free_malloc_strings(3, paths, strA, shell_name);
	return (NULL);
}

/**
 * search_abs_path - as it says
 * @search_var: var to search
 * @shell_name: shell name
 *
 * Return: string
 */
char *search_abs_path(char *shell_name, char *search_var)
{
	if (check_file_access(search_var) != 1)
	{
		return (NULL);
	}
	free(shell_name);
	return (search_var);
}

/**
 * concat_malloc_str - make malloc'd string writable
 * @string: malloc'd string to concat to
 * @first_str: first string to concat
 * @sec_str: second string to concat
 *
 * Return: void
 */
void concat_malloc_str(char *string, char *first_str, char *sec_str)
{
	_strcpy(string, "");
	_strcat(string, first_str);
	_strcat(string, sec_str);
}

/**
 * free_malloc_strings - free strings
 * @count: number of strings to free
 *
 * Return: void
 */
void free_malloc_strings(int count, ...)
{
	int i = 0;
	va_list ptr;

	va_start(ptr, count);

	while (i < count)
	{
		char *str = va_arg(ptr, char *);

		free(str);
		i++;
	}
}
