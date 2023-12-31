#include "main.h"

/**
 * builtin_env - prints the current environment
 *
 * Return: status
 */

int builtin_env(void)
{
	char **env = get_state()->env;

	while (*env != NULL)
		printf("%s\n", *env++);

	return (0);
}

/**
 * builtin_setenv - sets an environment variable
 *
 * @argv: argument vector
 *
 * Return: status
 */

int builtin_setenv(char **argv)
{
	int result;

	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "setenv: Too few arguments\n");
		return (1);
	}

	result = set_env(argv[1], argv[2]);
	if (result != 0)
	{
		fprintf(stderr, "setenv: Invalid variable name\n");
		return (2);
	}

	return (0);
}

/**
 * builtin_unsetenv - unsets an environment variable
 *
 * @argv: argument vector
 *
 * Return: status
 */

int builtin_unsetenv(char **argv)
{
	int result;

	if (argv[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Too few arguments\n");
		return (1);
	}

	result = unset_env(argv[1]);
	if (result != 0)
	{
		fprintf(stderr, "unsetenv: Invalid variable name\n");
		return (2);
	}

	return (0);
}
