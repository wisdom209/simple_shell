#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

extern char **environ;
char *old_dir;
char *curr_dir;
char *home;
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int exec_cmd(char **args, char **env);
char *_which(char *path, char **env);
/* char *_getenv(char *search_path, char **env); */
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env);
void change_dir(char **args, char **env);
void call_exit(char **args);
char *_getline();
/* char **copyenv(char **env); */
int _printf(const char *format, ...);
int _putchar(char c);
int isDelim(char c, char *delim);
int _setenv(char *env_name, char *env_value, int overwrite);
int _unsetenv(char *env_name);

int main(int argc, char **argv, char **env)
{
	/* home = getenv("HOME", env); */
	home = getenv("HOME");

	while (1)
	{
		write(STDIN_FILENO, "$ ", 3);
		char *cmd = read_cmd();
		char **args = split_lines(cmd, " \t\r\n");
		exec_cmd(args, env);
		/* free(args); */
		/* free(cmd); */
	}

	return (0);
}

char *read_cmd()
{
	size_t i = 0;
	char *buf = NULL;
	buf = _getline();

	if (buf == NULL)
	{
		kill(getpid(), 2);
	}

	return (buf);
}

int isDelim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/* TODO - fix potential malloc issues in this implementation */
char **split_lines(char *newstr, char *delimiter)
{
	if (newstr == NULL)
		return (NULL);
	char *str = strdup(newstr);
	strcat(str, delimiter); /* this line makes it work*/
	/* and i have no idea why??? */
	int str_size = strlen(str);
	int buffsize = str_size * str_size;
	int token_size = 0;
	int t_index = 0;
	while (str[t_index] != '\0')
	{
		if (isDelim(str[token_size], delimiter))
		{
			token_size++;
		}
		t_index++;
	}
	char **tokens = malloc(sizeof(char) * token_size);
	int indexer = -1;

	int i, j = 0, k = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (isDelim(str[i], delimiter))
		{
			continue;
		}

		indexer++;
		tokens[indexer] = malloc(sizeof(char) * str_size);
		k = 0;
		for (j = i; str[j] != '\0'; j++)
		{
			if (isDelim(str[j], delimiter))
			{
				i = j - 1;
				break;
			}

			tokens[indexer][k] = str[j];
			k++;
		}
	}
	tokens[indexer + 1] = NULL;
	/* free(str);
	free(newstr); */
	return (tokens);
}

int exec_cmd(char **args, char *env[])
{
	int a = call_inbuilt_func(args, env);
	char *location;
	char **env_two;

	if (a == 1)
		return (0);

	pid_t ch_pid = fork();

	if (ch_pid == 0)
	{
		a = 0;
		/* env_two = copyenv(environ); */
		location = _which(args[0], environ);

		execve(location, args, environ);

		exit(0);
	}
	else if (ch_pid > 0)
	{
		int status;
		wait(&status);
	}
	else
	{
		perror("bye\n");
		exit(1);
	}

	return (0);
}

/* TODO - incorrect commands more than two letters gives malloc error */
char *_which(char *search_var, char **env)
{
	int i = 0, size = 0;
	char *s;
	char **paths;
	/* env = copyenv(env); */

	if (search_var[0] == '/')
	{
		if (check_file_access(search_var) != 1)
		{
			printf("%s: command not found\n", search_var);
			return (NULL);
		}
		return (search_var);
	}
	else
	{
		/* s = getenv("PATH", env); */
		s = getenv("PATH");

		paths = split_lines(s, ":");

		char *strA = malloc(sizeof(search_var) * 10);
		strcat(strA, "/");
		strcat(strA, search_var);

		i = 0;
		while (paths[i])
		{
			char *checkstr = strcat(strdup(paths[i]), strA);

			if (check_file_access(checkstr) == 1)
			{
				/* free(strA); */
				return (checkstr);
			}

			/* free(checkstr); */
			i++;
		}
	}
	printf("%s: command not found\n", search_var);

	return (NULL);
}

int check_file_access(char *filepath)
{
	if (access(filepath, F_OK) != -1 && access(filepath, X_OK) != -1)
	{
		return (1);
	}
	return (0);
}
/*
char *_getenv(char *search_path, char **env)
{
	int i = 0, size = 0;
	char *s = NULL;
	char *a = NULL;
	int found = 0;
	if (search_path == NULL)
		return (NULL);

	while (env[i])
	{
		a = strdup(env[i]);
		char **stri = split_lines(a, "=");
		s = stri[0];

		if (strcmp(search_path, s) == 0)
		{
			found = 1;
			break;
		}
		free(stri[0]);
		free(stri[1]);
		free(stri);
		i++;
	}


	if (found == 1)
	{
		char **str = split_lines(a, "=");
		s = str[1];
		free(str[0]);
		free(str[1]);
		free(str);
	}
	else
		s = NULL;
	free(a);

	return (s);
}
*/
int call_inbuilt_func(char **args, char **env)
{
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
	return (0);
}

/* TODO - setenv pwd after path change */
void change_dir(char **args, char **env)
{
	/* TODO - FIX EMPTY ARG TO CD */
	curr_dir = getcwd(NULL, 0);
	if (args[2])
	{
		printf("bash : too many arguments\n");
		return;
	}
	else if (!args[1] || strcmp(args[1], "~") == 0 || strcmp(args[1], "--") == 0 || strcmp(args[1], "$HOME") == 0)
	{
		int a = chdir(home);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
	else if (args[1] && strcmp(args[1], "-") == 0)
	{
		int a = chdir(old_dir);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
	else if (args[1])
	{
		int a = chdir(args[1]);
		if (a != 0)
		{
			printf("bash : not a directory\n");
			return;
		}
		old_dir = curr_dir;
		return;
	}
}

void call_exit(char **args)
{
	/* TODO - get the implementations of atoi*/

	if (!args[1])
	{
		exit(0);
	}
	if (args[2])
	{
		printf("bash: illegal number of arguments");
	}

	if (args[1])
	{
		if (strlen(args[1]) == 1 && args[1][0] == '0')
		{
			exit(0);
		}
		else if (args[1][0] == '-')
		{
			printf("bash : illegal number\n");
			return;
		}
		else
		{

			int a = atoi(args[1]);

			if (a == 0)
			{
				printf("bash : illegal number\n");
				return;
			}
			if (a > INT_MAX || strlen(args[1]) > 10)
			{
				printf("bash : illegal number\n");
				return;
			}
			exit(a % 256);
		}

		return;
	}

	return;
}

/* char **copyenv(char **environ)
{
	int size = 0;
	while (environ[size])
	{
		size++;
	}

	char **new_environ = malloc(sizeof(char) * size * 1024);

	if (!new_environ)
	{
		return (NULL);
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		new_environ[i] = malloc(sizeof(char) * strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			for (int j = i - 1; i >= 0; i--)
			{
				free(new_environ[i]);
			}
			free(new_environ);
		}
		strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}
 */
char *_getline()
{
	int RL_BUFF_SIZE = 1024;
	int buffsize = RL_BUFF_SIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;
	int r;

	if (!buffer)
	{
		return (NULL);
	}

	while (1)
	{
		r = read(0, &c, 1);
		if (c == EOF || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return buffer;
		}
		else if (c == '\0')
		{
			return (NULL);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= buffsize)
		{
			buffsize += RL_BUFF_SIZE;
			buffer = realloc(buffer, buffsize);

			if (!buffer)
			{
				return (NULL);
			}
		}
	}
}

int _printf(const char *format, ...)
{
	int i = 0, count = 0, ret = 0;
	va_list ptr;

	va_start(ptr, format);

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
		}
		else
		{
			if (format[i + 1] == 'c')
			{
				char c = va_arg(ptr, int);

				if (c == 0)
					return (-1);

				_putchar(c);
				count = count + 1;
				i = i + 1;
			}
		}
		if (format[i + 1] == 's')
		{
			char *s = va_arg(ptr, char *);
			int j = 0;

			if (s == NULL)
				s = "(null)";

			while (s[j] != '\0')
			{
				_putchar(s[j]);
				count = count + 1;
				j++;
			}
			i = i + 1;
		}

		i++;
	}
	return (count);
}

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/* implement set env - malloc issues yet to */
/* implement set env - malloc issues yet to */
int _setenv(char *env_name, char *env_value, int overwrite)
{
	int i = 0, size = 0, highest = 0;

	if (env_name == NULL || env_value == NULL)
		return (-1);

	/* if (overwrite == 0 && getenv(env_name, environ))
		return (0); */
	if (overwrite == 0 && getenv(env_name))
		return (0);

	char *path_to_add = strdup(env_name);
	strcat(path_to_add, "=");
	strcat(path_to_add, env_value);

	char *new_env_add = malloc(sizeof(char) * strlen(path_to_add));

	putenv(path_to_add);

	return (0);
}

/* unset env... does not use malloc, should not need to be freed */
int _unsetenv(char *env_name)
{
	int i = 0, size = 0, location = 0, loc_size = 0;

	if (env_name == NULL)
		return (-1);
	/*
		if (!getenv(env_name, environ))
			return (0); */

	if (!getenv(env_name))
		return (0);

	while (env_name[i])
	{
		if (env_name[i] == '=')
		{
			return (-1);
		}
		i++;
	}

	size = 0;
	while (environ[size])
		size++;

	for (i = 0; i < size; i++)
	{
		char *a = split_lines(environ[i], "=")[0];
		if (strcmp(a, env_name) == 0)
		{
			location = i;
			break;
		}
	}

	for (i = location; i < size; i++)
	{
		if (environ[i + 1] == NULL)
		{
			environ[i] = NULL;
			break;
		}
		environ[i] = environ[i + 1];
	}
	return (0);
}
