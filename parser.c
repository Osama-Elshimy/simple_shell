#include "main.h"

#define DELIM " \n\t"

/**
 * tokenize - tokenize a string
 *
 * @line: string to tokenize
 *
 * Return: array of tokens
 */

char **tokenize(const char *line)
{
	char **tokens = NULL;
	char *token;
	char *line_copy;

	line_copy = strdup(line);
	if (line_copy == NULL)
	{
		perror("strdup");
		exit(1);
	}

	token = strtok(line_copy, DELIM);

	while (token)
	{
		string_array_push(&tokens, token);
		token = strtok(NULL, DELIM);
	}

	free(line_copy);
	return (tokens);
}
