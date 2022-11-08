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
	char *s = NULL, *strA = NULL;
	char **paths;

	if (search_var[0] == '/')
	{
		if (check_file_access(search_var) != 1)
		{
			_printf("%s: No such file or directory\n", shell_name);
			return (NULL);
		}
		return (search_var);
	}
	else
	{
		s = _getenv("PATH"), strA = malloc(sizeof(search_var) * 10);
		paths = split_lines(s, ":");

		if (strA == NULL)
			return (NULL);
		strcpy(strA, "");
		strcat(strA, "/");
		strcat(strA, search_var);
		while (paths[i])
		{
			char *checkstr = malloc(1024);

			if (checkstr == NULL)
				return (NULL);
			strcpy(checkstr, "");
			strcat(checkstr, paths[i]);
			strcat(checkstr, strA);
			if (check_file_access(checkstr) == 1)
				return (checkstr);
			i++;
		}
	}
	printf("%s: No such file or directory\n", shell_name);
	return (NULL);
}
/**
 * check_file_access - what it says
 * @filepath: parameter
 * Return: 1 on success
 */
int check_file_access(char *filepath)
{
	if (access(filepath, F_OK) != -1 && access(filepath, X_OK) != -1)
	{
		return (1);
	}
	return (0);
}
/**
 * call_inbuilt_func - what it says
 * @args: parameter
 * @env: env
 * Return: 1 on success
 */
int call_inbuilt_func(char **args, char **env)
{
	char *s;

	if (args[0] == NULL)
		return (1);
	if (strcmp(args[0], "cd") == 0)
	{
		change_dir(args, env);
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		call_exit(args);
		return (1);
	}
	if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] && args[2] && !args[3])
			_setenv(args[1], args[2], 0);
		else
			printf("invalid input\n");
		return (1);
	}
	if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[2])
		{
			printf("invalid number of args\n");
			return (1);
		}
		if (args[1])
			_unsetenv(args[1]);
		else
			printf("invalid input\n");
		return (1);
	}
	s = _which(args[0], environ);

	if (s == NULL)
		return (1);
	return (0);
}
