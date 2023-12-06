#include "main.h"

/**
 * builtin_exit - exits the shell
 *
 * @argv: argument vector
 *
 * Return: exit status
 */

int builtin_exit(char **argv)
{
	int status = 0;

	if (argv[1] != NULL)
	{
		status = atoi(argv[1]);

		if (status == 0 && _strcmp(argv[1], "0") != 0)
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	exit(status);
	return (status);
}
