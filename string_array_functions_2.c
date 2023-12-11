#include "main.h"

/**
 * string_array_contains - checks if a string array contains a string
 *
 * @arr: string array
 * @string: string to check
 *
 * Return: true if string is in array, false otherwise
 */

bool string_array_contains(char **arr, const char *string)
{
	size_t i;

	if (arr == NULL)
		return (false);

	for (i = 0; arr[i] != NULL; i++)
	{
		if (_strcmp(arr[i], string) == 0)
			return (true);
	}

	return (false);
}
