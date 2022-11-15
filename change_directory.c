#include "main.h"
#include "ctype.h"
/**
 * change_dir - change directory
 * @args: parameter
 * @env: env
 * @count: error count
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
			/* not_found_err(count, args[1]); */
			no_such_file_or_dir_err(count);
			free_malloc_strings(3, curr_dir, oldpwd);
			return;
		}
		_printf("%s\n", oldpwd);
		set_directory(curr_dir);
		free(oldpwd);
	}
	else if (!args[1] || _strcmp(args[1], "~") == 0 ||
			 _strcmp(args[1], "--") == 0 || _strcmp(args[1], "$HOME") == 0)
		cd_home(curr_dir, count);
	else if (args[1])
	{
		int a = chdir(args[1]);

		if (a != 0)
		{
			cant_cd_err(count, args[1]);
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
 * @count: error count
 *
 * Return: void
 */
void cd_home(char *curr_dir, int *count)
{
	char *home = _getenv("HOME");
	int a = chdir(home);

	if (a != 0)
	{

		cant_cd_err(count, home);
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
