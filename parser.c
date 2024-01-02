#include "main.h"

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

	if (string == NULL)
		return (NULL);

	while (string[i] != '\0')
	{
		if (string[i] == '#' && (i == 0 || isspace(string[i - 1])))
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

	if (string == NULL)
		return (NULL);
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
		if (string[i] == '$' && string[i + 1] != '\0' &&
			!isspace(string[i + 1]))
		{
			i++;
			while (string[i] != '\0' && !isspace(string[i]) &&
				   (isalpha(string[i]) || string[i] == '_'))
				string_cat_char(&var, string[i++]);
			if (is_valid_env(var))
				string_cat(&parsed_string, get_env(var));
			free(var);
			var = NULL;
			continue;
		}
		string_cat_char(&parsed_string, string[i++]);
	}
	return (parsed_string);
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
		if (string[i] == '"' || string[i] == '\'')
		{
			char *string_literal = parse_delimiter(string + i, string[i]);

			if (string_literal == NULL)
			{
				free(token), free(string_literal), string_array_free(&tokens);
				return (NULL);
			}

			string_cat_char(&token, string[i]);
			string_cat(&token, string_literal);
			string_cat_char(&token, string[i]);

			i += strlen(string_literal) + 2;
			free(string_literal);
			continue;
		}
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
		string_cat_char(&token, string[i++]);
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
			i += strlen(string_literal) + 2, string_cat(&token, string_literal),
				push_token(&tokens, &token), free(string_literal);
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

/**
 * parse_aliases - parses and expands aliases in a string
 *
 * @string: string to parse
 *
 * Return: parsed string
 */

char *parse_aliases(const char *string)
{
	char *parsed_string = NULL, *token = NULL, *alias = NULL, *check = NULL,
		 *cut_string = NULL, *expanded = NULL;
	char **commands = parse_operators(string);
	size_t i;

	if (commands == NULL)
		return (NULL);
	for (i = 0; commands[i] != NULL; i++)
	{
		if (is_operator(commands[i]))
		{
			string_cat(&parsed_string, commands[i]);
			if (commands[i + 1] != NULL)
				string_cat(&parsed_string, " ");
			continue;
		}
		token = get_first_token(commands[i]);
		alias = get_alias(token);
		check = get_first_token(alias);
		if (token != NULL && check != NULL && strcmp(token, check) == 0)
		{
			free(token), free(check), string_array_free(&commands);
			return (strdup(alias));
		}
		if (alias == NULL)
			string_cat(&parsed_string, commands[i]);
		else
		{
			cut_string = cut_first_token(commands[i]);
			expanded = parse_aliases(alias);
			string_cat(&parsed_string, expanded);
			string_cat(&parsed_string, cut_string);
			free(cut_string), free(expanded);
		}
		if (commands[i + 1] != NULL)
			string_cat(&parsed_string, " ");
		free(token), free(check);
	}
	string_array_free(&commands);
	return (parsed_string);
}
