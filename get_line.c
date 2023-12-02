#include "main.h"

/**
 * get_line - get line from stdin
 *
 * Return: pointer to line
 */

char *get_line(void)
{
	char *line = NULL;
	size_t size = 0;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	if (getline(&line, &size, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\nexit\n");

		free(line);
		exit(0);
	}

	return (line);
}
