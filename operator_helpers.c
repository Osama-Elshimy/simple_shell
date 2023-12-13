#include "main.h"

/**
 * is_operator - checks if a string is an operator
 *
 * @str: string to check
 *
 * Return: true if it is an operator, false otherwise
 */

bool is_operator(const char *str)
{
	char *operators[] = {"&&", "||", ";"};
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
	else
		return (UNDEF);
}
