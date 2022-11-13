#include "main.h"

/**
 * cant_cd_err - can't cd error
 * @count: error count
 * @shell_name: shell name
 * @path: path
 */
void cant_cd_err(int *count, char *shell_name, char *path)
{
	_printf("%s: %d: cd: can't cd to %s\n", shell_name, *count, path);
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
	_printf("%s: %d: exit: Illegal number: %s\n", shell_name, *count, num);
	*count = *count + 1;
}
