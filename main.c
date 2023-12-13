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

	if (argc >= 2)
	{
		state->fd = open(argv[1], O_RDONLY);
		if (state->fd == -1)
		{
			fprintf(stdout, "%s: 0: Can't open %s\n", argv[0], argv[1]);
			free_state();
			if (errno == EACCES)
				return (126);
			if (errno == ENOENT)
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

	free_state();
	return (0);
}
