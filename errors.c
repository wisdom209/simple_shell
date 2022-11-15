#include "main.h"

/**
 * cant_cd_err - can't cd error
 * @count: error count
 * @path: path
 */
void cant_cd_err(int *count, char *path)
{
	char *shell_name = _getenv("shell_name");

	_setenv("_std", "2", 1);
	_printf("%s: %d: cd: can't cd to %s\n", shell_name, *count, path);
	*count = *count + 1;
	_unsetenv("_std");
	free(shell_name);
}
/**
 * illegal_no_err - illegal number error
 * @count: error count
 * @num: num
 */
void illegal_no_err(int *count, char *num)
{
	char *shell_name = _getenv("shell_name");

	_setenv("_std", "2", 1);
	_printf("%s: %d: exit: Illegal number: %s\n", shell_name, *count, num);
	*count = *count + 1;
	_unsetenv("_std");
	free(shell_name);
}

/**
 * illegal_no_args - illegal number args
 * @count: error count
 * @cmd: num
 */
void illegal_no_args(int *count, char *cmd)
{
	char *shell_name = _getenv("shell_name");

	_setenv("_std", "2", 1);
	_printf("%s: %d: %s: Illegal number of arguments\n", shell_name, *count, cmd);
	*count = *count + 1;
	_unsetenv("_std");
	free(shell_name);
}
/**
 * not_found_err - file not found
 * @count: error count
 * @cmd: num
 */
void not_found_err(int *count, char *cmd)
{
	char *shell_name = _getenv("shell_name");

	_setenv("_std", "2", 1);
	_printf("%s: %d: %s: not found\n", shell_name, *count, cmd);
	*count = *count + 1;
	_unsetenv("_std");
	free(shell_name);
}
/**
 * no_such_file_or_dir_err - like it says
 * @count: error count
 */
void no_such_file_or_dir_err(int *count)
{
	char *shell_name = _getenv("shell_name");

	_setenv("_std", "2", 1);
	_printf("%s: ", shell_name);
	perror(NULL);
	*count = *count + 1;
	_unsetenv("_std");
	free(shell_name);
}
