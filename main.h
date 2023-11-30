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
void free_tokens(char **tokens);

void execute(char **tokens, char **envp, char *name);

#endif
