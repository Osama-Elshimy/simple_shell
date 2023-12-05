#include "main.h"

#define DELIM " \n\t"

/**
 * is_operator - checks if a string is an operator
 *
 * @str: string to check
 *
 * Return: true if it is an operator, false otherwise
 */

bool is_operator(const char *str)
{
	char *operators[] = {"&&", "||", ";", "#"};
	size_t len = sizeof(operators) / sizeof(operators[0]);
	size_t i;

	if (str == NULL)
		return (false);

	for (i = 0; i < len; i++)
	{
		if (strcmp(str, operators[i]) == 0)
			return (true);
	}

	return (false);
}

/**
 * get_operator_type - gets operator type
 *
 * @str: operator string
 *
 * Return: operator type
 */

enum Operator get_operator_type(const char *str)
{
	if (strcmp(str, "&&") == 0)
		return (AND);
	else if (strcmp(str, "||") == 0)
		return (OR);
	else if (strcmp(str, ";") == 0)
		return (SEMI);
	else if (strcmp(str, "#") == 0)
		return (HASH);
	else
		return (UNDEF);
}

/**
 * parse_commands - parses multiple commands from a line
 *
 * @line: line to parse
 *
 * Return: array of commands
 */

char **parse_commands(const char *line)
{
	char **commands = NULL;
	char *command = NULL;
	char *token = NULL;
	char *line_copy = NULL;

	if (line == NULL)
		return (NULL);
	line_copy = strdup(line);
	if (line_copy == NULL)
	{
		perror("strdup");
		exit(1);
	}
	token = _strtok(line_copy, DELIM);
	while (token)
	{
		if (is_operator(token))
		{
			if (command != NULL)
			{
				string_array_push(&commands, command);
				free(command);
				command = NULL;
			}
			string_array_push(&commands, token);
			token = _strtok(NULL, DELIM);
			continue;
		}
		cat_string(&command, token);
		cat_string(&command, " ");
		token = _strtok(NULL, DELIM);
	}
	if (command != NULL)
	{
		string_array_push(&commands, command);
		free(command);
	}
	free(line_copy);
	return (commands);
}

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

	if (line == NULL)
		return (NULL);

	line_copy = strdup(line);
	if (line_copy == NULL)
	{
		perror("strdup");
		exit(1);
	}

	token = _strtok(line_copy, DELIM);

	while (token)
	{
		string_array_push(&tokens, token);
		token = _strtok(NULL, DELIM);
	}

	free(line_copy);
	return (tokens);
}
