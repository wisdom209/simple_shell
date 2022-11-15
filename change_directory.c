#include "main.h"
#include "ctype.h"
/**
 * change_dir - change directory
 * @args: parameter
 * @env: env
 */
void change_dir(char **args, char **env __attribute__((unused)), int *count)
{
	char *curr_dir = getcwd(NULL, 0), *oldpw = _getenv("OLDPWD");

	if (oldpw == NULL)
		_setenv("OLDPWD", curr_dir, 1);
	free(oldpw);
	if (args[1] && _strcmp(args[1], "-") == 0)
	{
		char *oldpwd = _getenv("OLDPWD");
		int a = chdir(oldpwd);

		if (a != 0)
		{
			perror(NULL);
			free_malloc_strings(2, curr_dir, oldpwd);
			return;
		}
		_printf("%s\n", curr_dir);
		set_directory(curr_dir);
		free(oldpwd);
	}
	else if (!args[1] || _strcmp(args[1], "~") == 0 ||
			 _strcmp(args[1], "--") == 0 || _strcmp(args[1], "$HOME") == 0)
		cd_home(curr_dir);
	else if (args[1])
	{
		int a = chdir(args[1]);

		if (a != 0)
		{
			char *shell_name = _getenv("_");

			cant_cd_err(count, shell_name, args[1]);
			free(shell_name);
			free(curr_dir);
			return;
		}
		set_directory(curr_dir);
	}
	free(curr_dir);
}

/**
 * set_directory - sets directory
 * @curr_dir: where to set old dir to
 */
void set_directory(char *curr_dir)
{
	char *cwd = getcwd(NULL, 0);

	_setenv("OLDPWD", curr_dir, 1);
	_setenv("PWD", cwd, 1);

	free(cwd);
}

/**
 * cd_home - cd to home to directory
 * @curr_dir: current directory
 *
 * Return: void
 */
void cd_home(char *curr_dir)
{
	char *home = _getenv("HOME");
	int a = chdir(home);

	if (a != 0)
	{
		perror(NULL);
		free(curr_dir);
		free(home);
		return;
	}
	set_directory(curr_dir);
	free(home);
}

/**
 * free_arguments_and_buffer - free me pls
 * @args: args
 * @readbuf: read buffer
 *
 * Return: void
 */
void free_arguments_and_buffer(char **args, char readbuf[])
{
	free(args);
	free(readbuf);
}
