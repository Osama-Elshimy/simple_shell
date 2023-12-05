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
	static size_t buffer_index;
	static size_t bytes_read;
	char *line = NULL;
	size_t line_size = 0;
	char ch;

	while (true)
	{
		if (buffer_index == bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_index = 0;

			if (bytes_read == 0)
				return (line_size > 0 ? line : NULL);
		}

		if (line_size % BUFFER_SIZE == 0)
		{
			char *temp = realloc(line, line_size + BUFFER_SIZE);

			if (temp == NULL)
			{
				perror("realloc");
				free(line);
				exit(1);
			}
			line = temp;
		}

		ch = buffer[buffer_index++];
		if (ch == '\n')
		{
			line[line_size] = '\0';
			return (line);
		}
		line[line_size++] = ch;
	}
}

/**
 * display_prompt - displays prompt
 */

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
		fflush(stdout);
	}
}
