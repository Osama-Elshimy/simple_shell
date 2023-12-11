#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/* program state */

struct State
{
	char *name;
	char **env;
	char **aliases;
	int status;
	size_t count;
};

struct State *get_state(void);
void free_state(void);

/* input */

char *get_line(void);
void display_prompt(void);
int handle_input(void);

/* parse */

char **parse_operators(const char *string);
char **parse_command(const char *string);
char *parse_comments(const char *string);
char *parse_variables(const char *string);
char *parse_aliases(const char *string);

void cat_token(char **string, char **token);
void push_token(char ***tokens, char **token);
char *get_first_token(char *string);
char *cut_first_token(char *string);
char *parse_delimiter(const char *string, char delim);

enum Operator
{
	AND,
	OR,
	SEMI,
	UNDEF
};

bool is_operator(const char *str);
enum Operator get_operator_type(const char *str);
void handle_operator_and(char ***commands, int status);
void handle_operator_or(char ***commands, int status);
void handle_operator_semi(char ***commands);
void handle_operator_hash(char ***commands);
void handle_operator(char ***commands, int status);

char *_strtok(char *str, char *delim);

/* env */

extern char **environ;

char *get_env(const char *name);
int set_env(const char *name, const char *value);
int unset_env(const char *name);

bool is_valid_env(const char *name);
int get_env_index(const char *name);
char *assemble_env(const char *name, const char *value);

/* aliases */

char *get_alias(const char *name);
int set_alias(const char *name, const char *value);

int get_alias_index(const char *name);
char *assemble_alias(const char *name, const char *value);

/* commands */

void handle_commands(char **commands);
int handle_command(char **argv);
int builtin_exit(char **argv);
int builtin_cd(char **argv);
int builtin_env(void);
int builtin_alias(char **argv);
int builtin_setenv(char **argv);
int builtin_unsetenv(char **argv);
int execute(char **argv);

/* string functions */

size_t _strlen(const char *str);
char *_strdup(const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);

/* string array functions */

size_t string_array_length(char **arr);
void string_array_push(char ***arr, const char *str);
void string_array_remove(char ***arr, size_t index);
char **string_array_copy(char **arr);
bool string_array_contains(char **arr, const char *string);
void string_array_free(char ***arr);

/* memory functions */

void *_realloc(void *ptr, size_t size);

/* utility functions */

void string_cat(char **dest, const char *src);
void string_cat_char(char **dest, char src);
char *int_to_string(int num);
void inc_shlvl(void);
char *trim_whitespace(char *str);

#endif
