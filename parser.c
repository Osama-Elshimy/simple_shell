#include "main.h"

/**
 * parse_string - parses a string and replace variables
 *
 * @string: string to parse
 *
 * Return: parsed string
 */

char *parse_string(const char *string)
{
	char *parsed_comments;
	char *parsed_variables;

	if (string == NULL || *string == '\0')
		return (NULL);

	parsed_comments = parse_comments(string);
	if (parsed_comments == NULL)
		return (NULL);

	parsed_variables = parse_variables(parsed_comments);

	free(parsed_comments);
	return (parsed_variables);
}

/**
 * parse_operators - parses operators from a string into an array of
 * commands seperated by operators
 *
 * @string: string to parse
 *
 * Return: array of commands
 */

char **parse_operators(const char *string)
{
	char **tokens = NULL;
	char *token = NULL;
	size_t i = 0;

	if (string == NULL)
		return (NULL);

	while (string[i] != '\0')
	{
		if (string[i] == '&' && string[i + 1] == '&')
		{
			push_token(&tokens, &token);
			string_array_push(&tokens, "&&");
			i += 2;
			continue;
		}
		if (string[i] == '|' && string[i + 1] == '|')
		{
			push_token(&tokens, &token);
			string_array_push(&tokens, "||");
			i += 2;
			continue;
		}
		if (string[i] == ';')
		{
			push_token(&tokens, &token);
			string_array_push(&tokens, ";");
			i++;
			continue;
		}
		string_cat_char(&token, string[i]);
		i++;
	}

	push_token(&tokens, &token);
	return (tokens);
}

/**
 * parse_command - parses a command arguments from a string
 *
 * @string: string to parse
 *
 * Return: array of arguments
 */

char **parse_command(const char *string)
{
	char **tokens = NULL;
	char *token = NULL;
	size_t i = 0;

	if (string == NULL)
		return (NULL);

	while (string[i] != '\0')
	{
		if (string[i] == '\\' && string[i + 1] != '\0')
		{
			i++, string_cat_char(&token, string[i++]);
			continue;
		}
		if (string[i] == '"' || string[i] == '\'')
		{
			char *string_literal = parse_delimiter(string + i, string[i]);

			if (string_literal == NULL)
			{
				free(token), free(string_literal), string_array_free(&tokens);
				return (NULL);
			}
			i += _strlen(string_literal) + 2,
				string_cat(&token, string_literal), push_token(&tokens, &token),
				free(string_literal);
			continue;
		}
		if (isspace(string[i]))
		{
			push_token(&tokens, &token);
			while (isspace(string[i]))
				i++;
			continue;
		}
		string_cat_char(&token, string[i++]);
	}

	push_token(&tokens, &token);
	return (tokens);
}
