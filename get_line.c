#include "main.h"

#define BUFFER_SIZE 1024

/**
 * get_line - get line from stdin
 *
 * Return: pointer to line
 */

char *get_line(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index, buffer_size;
	char *line = NULL;
	size_t line_size = 0;
	int c;

	buffer_index = buffer_size = 0;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	fflush(stdout);

	while (true)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (buffer_size == 0)
			{
				if (line_size > 0)
					return (line);
				else
					return (NULL);
			}

			buffer_index = 0;
		}
		c = buffer[buffer_index++];

		if (line_size % BUFFER_SIZE == 0)
			line = realloc(line, line_size + BUFFER_SIZE);

		if (c == '\n' || c == EOF)
		{
			line[line_size] = '\0';
			return (line);
		}
		line[line_size++] = c;
	}
	return (line);
}
