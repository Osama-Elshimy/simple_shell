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

	(void)argc;

	state->name = argv[0];
	state->env = string_array_copy(environ);

	inc_shlvl();

	while (handle_input() == 0)
		;

	status = state->status;
	free_state();
	return (status);
}
