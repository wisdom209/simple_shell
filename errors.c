#include "main.h"
#include <errno.h>
/**
 * cant_cd_err - can't cd error
 * @count: error count
 * @shell_name: shell name
 * @path: path
 */
void cant_cd_err(int *count, char *shell_name, char *path)
{
	_setenv("std_err", "1", 1);
	_printf("%s: %d: cd: can't cd to %s\n", shell_name, *count, path);
	_unsetenv("std_err");
	*count = *count + 1;
}
/**
 * illegal_no_err - illegal number error
 * @count: error count
 * @shell_name: shell name
 * @num: num
 */
void illegal_no_err(int *count, char *shell_name, char *num)
{
	_setenv("std_err", "1", 1);
	errno = 2;
	_printf("%s: %d: exit: Illegal number: %s\n", shell_name, *count, num);
	_unsetenv("std_err");
	*count = *count + 1;
	_setenv("err_code", "2", 1);
}
/**
 * command_not_found_err - command not found
 * @count: error count
 * @shell_name: shell name
 * @cmd: num
 */
void command_not_found_err(int *count, char *shell_name, char *cmd)
{
	_setenv("std_err", "1", 1);
	errno = 127;
	_printf("%s: %d: %s: not found\n", shell_name, *count, cmd);
	_unsetenv("std_err");
	*count = *count + 1;
	_setenv("err_code", "127", 1);
}
