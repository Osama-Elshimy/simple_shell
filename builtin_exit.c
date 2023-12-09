#include "main.h"

/**
 * builtin_exit - exits the shell
 *
 * @argv: argument vector
 *
 * Return: 2 on failure
 */

int builtin_exit(char **argv)
{
	if (argv[1] != NULL)
	{
		int status = atoi(argv[1]);

		if (status == 0 && _strcmp(argv[1], "0") != 0)
		{
			fprintf(stderr, "%s: %lu: exit: Illegal number: %s\n",
					get_state()->name, get_state()->count, argv[1]);

			get_state()->status = 2;
			return (2);
		}

		exit(status);
	}

	exit(get_state()->status);
}
