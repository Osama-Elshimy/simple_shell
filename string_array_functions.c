#include "main.h"

/**
 * string_array_length - counts the number of elements in a string array
 *
 * @arr: string array
 *
 * Return: number of elements
 */

size_t string_array_length(char **arr)
{
	size_t count = 0;

	if (arr == NULL)
		return (0);

	while (arr[count] != NULL)
		count++;

	return (count);
}

/**
 * string_array_push - adds a string to the end of a string array
 *
 * @arr: string array
 * @str: string to add
 */

void string_array_push(char ***arr, const char *str)
{
	char **temp;
	size_t len;

	len = string_array_length(*arr);
	temp = _realloc(*arr, sizeof(char *) * (len + 2));
	if (temp == NULL)
	{
		perror("realloc");
		string_array_free(arr);
		exit(1);
	}

	temp[len] = _strdup(str);
	if (temp[len] == NULL)
	{
		perror("strdup");
		string_array_free(arr);
		exit(1);
	}

	temp[len + 1] = NULL;
	*arr = temp;
}

/**
 * string_array_copy - copies a string array
 *
 * @arr: string array
 *
 * Return: pointer to new string array
 */

char **string_array_copy(char **arr)
{
	char **copy = NULL;

	if (arr == NULL)
		return (NULL);

	while (*arr != NULL)
	{
		string_array_push(&copy, *arr);
		arr++;
	}

	return (copy);
}

/**
 * string_array_remove - removes a string from a string array
 *
 * @arr: string array
 * @index: index of string to remove
 */

void string_array_remove(char ***arr, size_t index)
{
	size_t i;
	size_t len;
	char **temp;

	len = string_array_length(*arr);
	if (index >= len)
		return;

	free((*arr)[index]);

	for (i = index; i < len; i++)
		(*arr)[i] = (*arr)[i + 1];

	temp = _realloc(*arr, sizeof(char *) * (len));
	if (temp == NULL)
	{
		perror("realloc");
		return;
	}

	*arr = temp;
}

/**
 * string_array_free - frees a string array
 *
 * @arr: string array
 */

void string_array_free(char ***arr)
{
	int i;

	if (arr == NULL || *arr == NULL)
		return;

	for (i = 0; (*arr)[i] != NULL; i++)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}

	free(*arr);
	*arr = NULL;
}
