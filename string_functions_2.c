#include "main.h"

/**
 * _atoi - convert string to an integer
 *
 * @s: string to convert
 *
 * Return: integer value of the string
 */

int _atoi(char *s)
{
	int sign = 1;
	unsigned int result = 0;
	int i = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (isdigit(s[i]))
		{
			while (isdigit(s[i]))
			{
				result = result * 10 + (s[i] - '0');

				i++;
			}

			result *= sign;

			return (result);
		}
	}

	return (0);
}

/**
 * _strncmp - compares two strings
 *
 * @str1: first string
 * @str2: second string
 * @n: number of bytes to compare
 *
 * Return: 0 if equal, otherwise difference
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			return ((str1[i] < str2[i]) ? -1 : 1);

		if (str1[i] == '\0' || str2[i] == '\0')
			return (0);
	}

	return (0);
}
