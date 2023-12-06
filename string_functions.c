#include "main.h"

/**
 * _strlen - returns the length of a string
 *
 * @str: string to get the length of
 *
 * Return: length
 */

size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
		length++;

	return (length);
}

/**
 * _strdup - returns a newly allocated string
 *
 * @src: input string
 *
 * Return: new string
 */

char *_strdup(const char *src)
{
	char *str;
	char *p;
	int len = 0;

	while (src[len])
		len++;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);

	p = str;
	while (*src)
		*p++ = *src++;

	*p = '\0';

	return (str);
}

/**
 * _strcat - append the src string to the dest string,
 *
 * @dest: input string
 * @src: string to append
 *
 * Return: new string
 */

char *_strcat(char *dest, const char *src)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;

	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 *
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if s1 and s2 are equal
 *         a negative number if s1 is less than s2
 *         a positive number if s1 is greater than s2
 */

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strcpy - copy the string pointed to by src to dest
 *
 * @src: source string pointer
 * @dest: destination string pointer
 *
 * Return: pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	char *dest_ptr = dest;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (dest_ptr);
}
