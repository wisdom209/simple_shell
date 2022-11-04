#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
extern char **__environ;

char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int exec_cmd(char **args, char **env);
char *_which(char *path, char **env);
char *_getenv(char *search_path, char **env);
int check_file_access(char *filepath);

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
		kill(getpid(), 2);

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

int exec_cmd(char **args, char **env)
{

	pid_t ch_pid = fork();
	char *location = NULL;

	if (ch_pid == 0)
	{
		location = _which(args[0], env);
		execve(location, args, NULL);
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
		return (search_var);
	}
	else
	{
		s = _getenv("PATH", env);

		paths = split_lines(s, ":");

		char *strA = malloc(sizeof(search_var) * 2);
		strcat(strA, "/");
		strcat(strA, search_var);

		i = 0;
		while (paths[i])
		{
			char *checkstr = strcat(paths[i], strA);
			if (check_file_access(checkstr) == 1)
			{
				free(strA);
				return (checkstr);
			}
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
		s = strtok(env[i], "=");

		if (strcmp(search_path, s) == 0)
			break;

		i++;
	}
	/* gets the other path of PATH searched */
	s = strtok(NULL, "=");

	return (s);
}
