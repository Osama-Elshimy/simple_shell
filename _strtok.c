#include "main.h"

/**
 * is_delim - checks if a character is a delimiter
 *
 * @c: character to check
 * @delim: string of delimiters
 *
 * Return: true if c is a delimiter
 */

static bool is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}

/**
 * _strtok - tokenizes a string
 *
 * @str: string to tokenize
 * @delim: string of delimiters
 *
 * Return: pointer to the next token
 */

char *_strtok(char *str, char *delim)
{
	static char *backup_string;
	char *ret;

	if (str == NULL)
	{
		str = backup_string;
		if (str == NULL)
			return (NULL);
	}

	while (is_delim(*str, delim))
		str++;

	if (*str == '\0')
		return (NULL);

	ret = str;

	while (*str != '\0' && !is_delim(*str, delim))
		str++;

	if (*str != '\0')
	{
		*str = '\0';
		backup_string = str + 1;
	}
	else
		backup_string = str;

	return (ret);
}
