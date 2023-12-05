#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* input */

char *get_line(void);
void display_prompt(void);

/* parse */

char **tokenize(const char *line);
char **parse_commands(const char *line);

enum Operator
{
	AND,
	OR,
	SEMI,
	HASH,
	UNDEF
};

bool is_operator(const char *str);
enum Operator get_operator_type(const char *str);
void handle_operator_and(char ***commands, int status);
void handle_operator_or(char ***commands, int status);
void handle_operator_semi(char ***commands);
void handle_operator_hash(char ***commands);
void handle_operator(char ***commands, int status);

/* commands */

void handle_commands(char **commands, char **envp);
int handle_command(char **argv, char **envp);
int builtin_exit(char **argv);
int builtin_setenv(char **argv);
int builtin_unsetenv(char **argv);
int builtin_cd(char **argv);
int execute(char **tokens, char **envp);

/* utility */

char *get_exec_path(const char *command);
void cat_string(char **dest, const char *src);
int string_array_length(char **arr);
void string_array_push(char ***arr, const char *str);
void string_array_free(char ***arr);
char *_strtok(char *str, char *delim);

#endif
