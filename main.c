#include "main.h"
#include <limits.h>

/**
 * main - entry point
 *
 * Description: a simple shell program
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */

int main(int argc, char **argv)
{
	struct State *state = get_state();

	if (argc > 1)
		return (0);

	state->name = argv[0];
	state->env = string_array_copy(environ);

	inc_shlvl();

	while (true)
	{
		char *line = NULL;
		char **commands = NULL;

		display_prompt();
		line = get_line();
		if (line == NULL)
			break;

		commands = parse_commands(line);
		handle_commands(commands);

		string_array_free(&commands);
		free(line);
		line = NULL;
	}

	free_state();
	return (0);
}
