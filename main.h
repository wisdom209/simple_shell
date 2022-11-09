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

extern char **environ;
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
int check_token_length(char *str, char *delimiter,
					   int t_index, int token_size);
int exec_cmd(char **args, char **env);
char *_which(char *path, char **env);
char *_getenv(char *search_path);
int check_file_access(char *filepath);
int call_inbuilt_func(char **args, char **env);
void change_dir(char **args, char **env);
void call_exit(char **args);
char *_getline();
/* char **copyenv(char **env); */
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

#endif /* MAIN_H */
