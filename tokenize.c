#include "main.h"

/**
 * get_tokens_len - get tokens length
 *
 * @line: string to tokenize
 *
 * Return: number of tokens or -1
 */

static int get_tokens_len(const char *line)
{
	int count = 0;
	char *token;
	char *line_copy;

	line_copy = strdup(line);
	if (!line_copy)
	{
		perror("strdup");
		return (-1);
	}

	token = strtok(line_copy, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}

	free(line_copy);
	return (count);
}

/**
 * tokenize - tokenize a string
 *
 * @line: string to tokenize
 *
 * Return: array of tokens or NULL
 */

char **tokenize(const char *line)
{
	char *line_copy;
	char **tokens = NULL;
	int tokens_len = get_tokens_len(line);
	char *token;
	int i;

	if (tokens_len == -1)
		return (NULL);

	tokens = calloc((tokens_len + 1), sizeof(char *));
	if (!tokens)
	{
		perror("calloc");
		return (NULL);
	}

	line_copy = strdup(line);
	if (!line_copy)
	{
		perror("strdup");
		free(tokens);
		return (NULL);
	}

	token = strtok(line_copy, " ");
	for (i = 0; i < tokens_len; i++)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_tokens(tokens);
			perror("strdup");
			return (NULL);
		}
		token = strtok(NULL, " ");
	}

	tokens[tokens_len] = NULL;
	free(line_copy);
	return (tokens);
}

/**
 * free_tokens - free tokens array
 *
 * @tokens: array of tokens
 */

void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]);

	free(tokens);
}
