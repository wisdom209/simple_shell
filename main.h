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

#define NOT_A_DIRECTORY 1
#define CANT_CD 2
#define ILLEGAL_NO 3

extern char **environ;
void free_malloc_strings(int count, ...);
char **_split(char *line, char *delimiter);
char *_strtok(char *str, const char *delim);
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int check_token_length(char *str, char *delimiter,
					   int t_index, int token_size);
int exec_cmd(char **args, char **env, char readbuf[], int *count);
char *_which(char *path, char **env);
char *_getenv(char *search_path);
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env, char readbuf[], int *count);
char *search_abs_path(char *shell_name, char *search_var);
void concat_malloc_str(char *str, char *first_str, char *sec_str);
void change_dir(char **args, char **env, int *count);
void call_exit(char **args, char readbuf[], int *count);
char *_getline();
int _printf(const char *format, ...);
int _putchar(char c);
int isDelim(char c, char *delim);
int _setenv(char *env_name, char *env_value, int overwrite);
int _unsetenv(char *env_name);
void set_directory(char *curr_dir);
int check_unsetenv(char **args);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strdup(char *src);
char *_strcpy(char *destination, char *source);
void cd_home(char *curr_dir);
void free_arguments_and_buffer(char **args, char readbuf[]);
void set_location_of_var_to_unset(int size, char *env_name, int *location);
int print_digits(int *i, va_list ptr, const char *format, int *count);
int print_num(long num, int *count);
int print_string(int *i, va_list ptr, const char *format, int *count);
void cant_cd_err(int *count, char *shell_name, char *path);
void illegal_no_err(int *count, char *shell_name, char *num);
void printenv(void);
int handle_exit_num_errors(int a, int *count, char **args);
int _isDigit(char *s);
#endif /* MAIN_H */
