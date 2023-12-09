#include "main.h"

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
	int status;

	(void)argc;

	state->name = argv[0];
	state->env = string_array_copy(environ);

	inc_shlvl();

	while (true)
	{
		char *line = NULL;
		char *parsed_line = NULL;
		char **commands = NULL;

		display_prompt();
		line = get_line();
		if (line == NULL)
			break;

		parsed_line = parse_string(line);
		commands = parse_operators(parsed_line);
		handle_commands(commands);

		free(line);
		free(parsed_line);
		string_array_free(&commands);
	}

	status = state->status;
	free_state();
	return (status);
}
