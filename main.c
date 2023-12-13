#include "main.h"

/**
 * main - entry point
 *
 * Description: a simple shell program
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: status
 */

int main(int argc, char **argv)
{
	struct State *state = get_state();
	int status;

	if (argc >= 2)
	{
		state->fd = open(argv[1], O_RDONLY);
		if (state->fd == -1)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
			free_state();
			return (127);
		}
	}
	else
	{
		state->fd = STDIN_FILENO;
		state->prompt = PROMPT;
	}

	state->name = argv[0];
	state->env = string_array_copy(environ);

	while (handle_input())
		;

	status = state->status;
	free_state();
	return (status);
}
