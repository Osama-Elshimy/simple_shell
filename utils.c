#include "main.h"

/**
 * cat_string - concatenate two strings
 *
 * @dest: destination string
 * @src: source string
 */

void cat_string(char **dest, const char *src)
{
	char *temp;
	int len;

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
 * string_array_length - counts the number of elements in a string array
 *
 * @arr: string array
 *
 * Return: number of elements
 */

int string_array_length(char **arr)
{
	int count = 0;

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
	int len;

	if (*arr == NULL)
	{
		*arr = malloc(sizeof(char *) * 2);
		if (*arr == NULL)
		{
			perror("malloc");
			exit(1);
		};
		(*arr)[0] = strdup(str);
		if ((*arr)[0] == NULL)
		{
			perror("strdup");
			free(*arr);
			exit(1);
		}
		(*arr)[1] = NULL;
		return;
	}

	len = string_array_length(*arr);
	temp = realloc(*arr, sizeof(char *) * (len + 2));
	if (temp == NULL)
	{
		perror("realloc");
		string_array_free(arr);
		exit(1);
	}

	temp[len] = strdup(str);
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