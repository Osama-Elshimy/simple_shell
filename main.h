#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *get_line(void);
char **tokenize(const char *line);
int execute(char **tokens, char **envp);
char *get_exec_path(const char *command);

void exit_builtin(char **argv);
int handle_command(char **argv, char **envp);

void cat_string(char **dest, const char *src);
int string_array_length(char **arr);
void string_array_push(char ***arr, const char *str);
void string_array_free(char ***arr);

char *_strtok(char *str, char *delim);
unsigned int is_delim(char c, char *delim);

#endif
