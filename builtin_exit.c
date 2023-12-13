#include "main.h"

/**
 * builtin_exit - exits the shell
 *
 * @argv: argument vector
 */

void builtin_exit(char **argv)
{
	int status = get_state()->status;

	if (argv[1] != NULL)
	{
		size_t i;

		status = atoi(argv[1]);

		for (i = 0; argv[1][i] != '\0'; i++)
		{
			if (i == 0 && argv[1][i] == '+')
				continue;

			if (!isdigit(argv[1][i]))
			{
				fprintf(stderr, "%s: %lu: exit: Illegal number: %s\n",
						get_state()->name, get_state()->count, argv[1]);
				status = 2;
				break;
			}
		}
	}

	free_state();
	string_array_free(&argv);
	exit(status);
}
