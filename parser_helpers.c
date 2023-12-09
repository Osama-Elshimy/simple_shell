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
	if (*token == NULL)
		return;

	string_array_push(tokens, *token);
	free(*token);
	*token = NULL;
}

/**
 * parse_comments - parses comments from a string
 *
 * @string: string to parse
 *
 * Return: parsed string
 */

char *parse_comments(const char *string)
{
	char *parsed_string = NULL;
	size_t i = 0;

	while (string[i] != '\0')
	{
		if (string[i] == '#' &&
			(_strlen(parsed_string) == 0 || isspace(string[i - 1])))
			break;

		string_cat_char(&parsed_string, string[i++]);
	}

	return (parsed_string);
}

/**
 * parse_variables - parses and expands variables in a string
 *
 * @string: string to parse
 *
 * Return: parsed string
 */

char *parse_variables(const char *string)
{
	char *parsed_string = NULL;
	char *var = NULL;
	size_t i = 0;

	while (string[i] != '\0')
	{
		if (string[i] == '$' && string[i + 1] == '?')
		{
			var = int_to_string(get_state()->status);
			cat_token(&parsed_string, &var);
			i += 2;
			continue;
		}
		if (string[i] == '$' && string[i + 1] == '$')
		{
			var = int_to_string(getpid());
			cat_token(&parsed_string, &var);
			i += 2;
			continue;
		}
		if (string[i] == '$' &&
			(!isspace(string[i + 1]) && string[i + 1] != '\0'))
		{
			i++;

			while (!isspace(string[i]) && string[i] != '\0' && string[i] != '$')
				string_cat_char(&var, string[i++]);

			if (var != NULL)
			{
				string_cat(&parsed_string, get_env(var));
				free(var);
				var = NULL;
			}
			continue;
		}
		string_cat_char(&parsed_string, string[i++]);
	}

	return (parsed_string);
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
		return (NULL);

	if (string == delimiter_end)
		string_cat_char(&parsed_delimter, '\0');

	while (string != delimiter_end)
	{
		string_cat_char(&parsed_delimter, *string);
		string++;
	}

	return (parsed_delimter);
}
