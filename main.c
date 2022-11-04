#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int exec_cmd(char **args, char **env);
char *_which(char *path, char **env);
char *_getenv(char *search_path, char **env);
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env);
void change_dir(char **args, char **env);
void call_exit(char **args);
char **copyenv(char **env);

int main(int argc, char **argv, char **env)
{
	while (1)
	{
		printf("$ ");
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
	int result = getline(&buf, &i, stdin);

	if (result < 0)
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

	if (a == 1)
		return (0);

	pid_t ch_pid = fork();

	if (ch_pid == 0)
	{
		a = 0;
		char **env_two = copyenv(environ);
		char *location = _which(args[0], env);

		execve(location, args, env_two);
		exit(1);
	}
	else if (ch_pid > 0)
	{
		int status;
		do
		{
			waitpid(ch_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
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

	if (search_var[0] == '/')
	{
		if (check_file_access(search_var) != 1)
			printf("%s: command not found\n", search_var);
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
	free(env);
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
		s = strtok(env[i], "=");

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
