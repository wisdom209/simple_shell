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
extern char *old_dir;
extern char *curr_dir;
extern char *shell_name;
extern char *home;
char *read_cmd();
char **split_lines(char *cmd, char *delimiters);
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

#endif /* MAIN_H */
