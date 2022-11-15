#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

/* Global environment variable */
extern char **environ;

/* split_string.c */
char **_split(char *line, char *delimiter);

/* call inbuilt functions.c */
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env, char readbuf[], int *count);
void printenv(void);
int check_unsetenv(char **args, int *count);

/* _strtok.c */
char *_strtok(char *str, const char *delim);

/* getline.c */
char *read_cmd();
char *_getline();

/* stringhelpers.c */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strdup(char *src);
char *_strcpy(char *destination, char *source);

/* Environment handlers.c */
int _setenv(char *env_name, char *env_value, int overwrite);
int _unsetenv(char *env_name);
char *_getenv(char *search_path);
void set_location_of_var_to_unset(int size, char *env_name, int *location);

/* exec_cmd.c */
int exec_cmd(char **args, char **env, char readbuf[], int *count);

/* which.c */
char *_which(char *path, char **env, int *count);
char *search_abs_path(char *shell_name, char *search_var);
void free_malloc_strings(int count, ...);
void concat_malloc_str(char *str, char *first_str, char *sec_str);

/* _printf.c */
int print_digits(int *i, va_list ptr, const char *format, int *count);
int print_num(long num, int *count);
int print_string(int *i, va_list ptr, const char *format, int *count);
int _printf(const char *format, ...);
int _putchar(char c);

/* exit handlers.c */
int _isDigit(char *s);
void call_exit(char **args, char readbuf[], int *count);
int handle_exit_num_errors(int a, int *count, char **args);


/* change_directory.c */
void change_dir(char **args, char **env, int *count);
void cd_home(char *curr_dir, int *count);
void set_directory(char *curr_dir);
void free_arguments_and_buffer(char **args, char readbuf[]);

/* errors.c */
void cant_cd_err(int *count, char *path);
void illegal_no_err(int *count, char *num);
void illegal_no_args(int *count, char *cmd);
void not_found_err(int *count, char *cmd);
void no_such_file_or_dir_err(int *count);

#endif /* MAIN_H */
