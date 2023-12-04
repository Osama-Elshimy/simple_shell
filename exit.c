#include "main.h"

/**
 * exit_builtin - exits the shell
 *
 * @argv: argument vector
 */

void exit_builtin(char **argv)
{
	int status = 0;

	if (argv[1] != NULL)
	{
		status = atoi(argv[1]);

		if (status == 0 && strcmp(argv[1], "0") != 0)
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	string_array_free(&argv);
	exit(status);
}
