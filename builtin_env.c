#include "main.h"

/**
 * builtin_env - prints the current environment
 *
 * Return: 0
 */

int builtin_env(void)
{
	char **env = get_state()->env;
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);

	return (0);
}

/**
 * builtin_setenv - sets an environment variable
 *
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
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
		return (1);

	return (0);
}

/**
 * builtin_unsetenv - unsets an environment variable
 *
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
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
		perror("unsetenv");
		return (1);
	}

	return (0);
}
