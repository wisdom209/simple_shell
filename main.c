#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;
char *old_dir;
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int exec_cmd(char **args, char **env);
char *_which(char *path, char **env);
char *_getenv(char *search_path, char **env);
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env);
void change_dir(char **args, char **env);
void call_exit(char **args);
char *_getline();
char **copyenv(char **env);
int _printf(const char *format, ...);
int _putchar(char c);

int main(int argc, char **argv, char **env)
{
	
	while (1)
	{
		write(STDIN_FILENO, "$ ", 3);
		char *cmd = read_cmd();
		char **args = split_lines(cmd, " \t\r\n");
		exec_cmd(args, env);
		free(args);
		free(cmd);
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

char **split_lines(char *cmd, char *delimiters)
{
	char **tokens = malloc(sizeof(cmd) * 2 * 1024);
	char *token = strtok(cmd, delimiters);
	int pos = 0;

	if (!tokens)
		exit(1);

	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, delimiters);
	}
	tokens[pos] = NULL;

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
		env_two = copyenv(environ);
		location = _which(args[0], env_two);

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

char *_which(char *search_var, char **env)
{
	int i = 0, size = 0;
	char *s;
	char **paths;
	env = copyenv(env); 

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
		s = _getenv("PATH", env);

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
				free(strA);
				return (checkstr);
			}

			free(checkstr);
			i++;
		}
	}
	printf("%s: command not found\n", search_var);

	return (search_var);
}

int check_file_access(char *filepath)
{
	if (access(filepath, F_OK) != -1 && access(filepath, X_OK) != -1)
	{
		return (1);
	}
	return (0);
}

char *_getenv(char *search_path, char **env)
{
	int i = 0, size = 0;
	char *s = NULL;

	while (env[i])
	{
		char *a = strdup(env[i]);
		s = strtok(a, "=");

		if (strcmp(search_path, s) == 0)
			break;
		i++;
	}
	/* gets the other path of PATH searched */
	s = strtok(NULL, "=");

	return (s);
}

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

void change_dir(char **args, char **env)
{
	/* TODO - FIX EMPTY ARG TO CD */
	if (args[2])
	{
		printf("bash : too many arguments\n");
		return;
	}
	else if (args[1])
	{
		int a = chdir(args[1]);
		if (a != 0)
			printf("bash : not a directory\n");
		return;
	}
	else
	{
		char *home = _getenv("PWD", env);
		int a = chdir(home);
		if (a != 0)
			printf("bash : not a directory\n");
		return;
	}
}

void call_exit(char **args)
{
	if (!args[1])
	{
		exit(1);
	}
	return;
}

char **copyenv(char **environ)
{
	int size = 0;
	while (environ[size])
	{
		size++;
	}

	char **new_environ = malloc(sizeof(char) * size + 1);

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
