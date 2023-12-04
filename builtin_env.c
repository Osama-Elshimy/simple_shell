#include "main.h"

/**
 * _setenv - sets an environment variable
 *
 * @argv: argument vector
 *
 * Return: void
 */

int builtin_setenv(char **argv)
{
	int result;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "setenv: Too few arguments\n");
		return (1);
	}

	result = setenv(argv[1], argv[2], 1);
	if (result != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}

/**
 * _unsetenv - unsets an environment variable
 *
 * @argv: argument vector
 *
 * Return: void
 */

int builtin_unsetenv(char **argv)
{
	int result;

	if (argv[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Too few arguments\n");
		return (1);
	}

	result = unsetenv(argv[1]);

	if (result != 0)
	{
		perror("unsetenv");
		return (1);
	}

	return (0);
}
