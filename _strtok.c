#include "main.h"

/**
 * is_delim - checks if a character is a delimiter
 *
 * @c: character to check
 * @delim: string of delimiters
 *
 * Return: true if c is a delimiter
 */

unsigned int is_delim(char c, char *delim)
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

	if (!str)
		str = backup_string;
	if (!str)
		return (NULL);

	while (true)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}

	ret = str;

	while (true)
	{
		if (*str == '\0')
		{
			backup_string = str;
			return (ret);
		}
		if (is_delim(*str, delim))
		{
			*str = '\0';
			backup_string = str + 1;
			return (ret);
		}
		str++;
	}
}
