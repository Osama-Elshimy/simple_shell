#include "main.h"

/**
 * _setenv - sets an environment variable
 *
 * @argv: argument vector
 *
 * Return: void
 */

void _setenv(char **argv)
{
	int result;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "setenv: Too few arguments\n");
		string_array_free(&argv);
		return;
	}

	result = setenv(argv[1], argv[2], 1);

	if (result != 0)
		perror("setenv");

	string_array_free(&argv);
}

/**
 * _unsetenv - unsets an environment variable
 *
 * @argv: argument vector
 *
 * Return: void
 */

void _unsetenv(char **argv)
{
	int result;

	if (argv[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Too few arguments\n");
		string_array_free(&argv);
		return;
	}

	result = unsetenv(argv[1]);

	if (result != 0)
		perror("unsetenv");

	string_array_free(&argv);
}
