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
			char *temp = _realloc(line, line_size + BUFFER_SIZE);

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

/**
 * handle_input - handles input
 *
 * Return: 0 on success, 1 on EOF
 */

int handle_input(void)
{
	char *line = NULL;
	char *parsed_aliases = NULL;
	char *parsed_comments = NULL;
	char *parsed_variables = NULL;
	char **commands = NULL;

	display_prompt();
	line = get_line();
	if (line == NULL)
		return (1);

	parsed_aliases = parse_aliases(line);
	parsed_comments = parse_comments(parsed_aliases);
	parsed_variables = parse_variables(parsed_comments);
	commands = parse_operators(parsed_variables);
	handle_commands(commands);

	free(line);
	free(parsed_aliases);
	free(parsed_comments);
	free(parsed_variables);
	string_array_free(&commands);
	return (0);
}
