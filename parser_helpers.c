#include "main.h"

/**
 * cat_token - concatenates a token to a string
 *
 * @string: string
 * @token: token to concatenate
 */

void cat_token(char **string, char **token)
{
	if (*token == NULL)
		return;

	string_cat(string, *token);
	free(*token);
	*token = NULL;
}
/**
 * push_token - pushes a token to tokens array
 *
 * @tokens: tokens array
 * @token: token to push
 */

void push_token(char ***tokens, char **token)
{
	char *trimmed = NULL;

	if (*token == NULL)
		return;

	trimmed = trim_whitespace(*token);
	string_array_push(tokens, trimmed);
	free(*token);
	*token = NULL;
}

/**
 * cut_first_token - cuts the first token from a string
 *
 * @string: string
 *
 * Return: token
 */

char *cut_first_token(char *string)
{
	char *token = NULL;
	char *string_copy = NULL;
	char *cut_string = NULL;

	if (string == NULL)
		return (NULL);

	string_copy = _strdup(string);
	token = _strtok(string_copy, " \t\n");

	cut_string = _strdup(string + _strlen(token));

	free(string_copy);
	return (cut_string);
}

/**
 * get_first_token - gets the first token from a string
 *
 * @string: string
 *
 * Return: token
 */

char *get_first_token(char *string)
{
	char *string_copy = NULL;
	char *token = NULL;

	if (string == NULL)
		return (NULL);

	string_copy = _strdup(string);
	token = _strdup(_strtok(string_copy, " \t\n"));

	free(string_copy);
	return (token);
}

/**
 * parse_delimiter - parses a delimiter
 *
 * @string: string to parse
 * @delim: delimiter
 *
 * Return: parsed string
 */

char *parse_delimiter(const char *string, char delim)
{
	char *parsed_delimter = NULL;
	const char *delimiter_end = NULL;

	string++;
	delimiter_end = strchr(string, delim);

	if (delimiter_end == NULL)
	{
		fprintf(stderr, "Syntax Error: Unmatched delimiter %c\n", delim);
		return (NULL);
	}

	if (string == delimiter_end)
		string_cat_char(&parsed_delimter, '\0');

	while (string != delimiter_end)
	{
		string_cat_char(&parsed_delimter, *string);
		string++;
	}

	return (parsed_delimter);
}
