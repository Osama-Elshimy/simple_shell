#include "main.h"

/**
 * string_cat - concatenates two strings
 *
 * @dest: destination string
 * @src: source string
 */

void string_cat(char **dest, const char *src)
{
	char *temp;
	size_t len;

	if (src == NULL)
		return;

	if (*dest == NULL)
	{
		*dest = malloc(strlen(src) + 1);
		if (*dest == NULL)
		{
			perror("malloc");
			exit(1);
		}

		strcpy(*dest, src);
		return;
	}

	len = strlen(*dest) + strlen(src) + 1;
	temp = realloc(*dest, len);
	if (temp == NULL)
	{
		perror("realloc");
		free(*dest);
		exit(1);
	}

	strcat(temp, src);
	*dest = temp;
}

/**
 * string_cat_char - concatenates char to string
 *
 * @dest: destination string
 * @src: char to add
 */

void string_cat_char(char **dest, char src)
{
	char *temp;
	size_t len;

	if (dest == NULL)
		return;

	len = *dest == NULL ? 2 : strlen(*dest) + 2;

	temp = realloc(*dest, len);
	if (temp == NULL)
	{
		perror("realloc");
		exit(1);
	}

	temp[len - 2] = src;
	temp[len - 1] = '\0';
	*dest = temp;
}

/**
 * int_to_string - converts integer to string
 *
 * @number: integer to convert
 *
 * Return: pointer to string
 */

char *int_to_string(int number)
{
	char *digits = "0123456789";
	char *buf;
	int len = number ? 0 : 1;
	unsigned int i;
	unsigned int abs_num = (number < 0) ? -number : number;

	if (number < 0)
		len++;

	for (i = abs_num; i > 0; i /= 10)
		len++;

	buf = calloc(len + 1, sizeof(char));
	if (buf == NULL)
	{
		perror("calloc");
		exit(1);
	}

	if (number < 0)
		buf[0] = '-';

	i = len - 1;

	/* clang-format off */
	do {
		/* clang-format on */
		buf[i--] = digits[abs_num % 10];
		abs_num /= 10;
	} while (abs_num > 0);

	buf[len] = '\0';
	return (buf);
}

/**
 * trim_whitespace - trims whitespace
 *
 * @str: string
 *
 * Return: trimmed string
 */

char *trim_whitespace(char *str)
{
	char *end;

	while (isspace(*str))
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	*(end + 1) = '\0';

	return (str);
}
