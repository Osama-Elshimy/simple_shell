#include "main.h"

static struct State *state;

/**
 * init_state - initializes the state
 */

static void init_state(void)
{
	state = malloc(sizeof(struct State));
	if (state == NULL)
	{
		perror("malloc");
		exit(1);
	}

	state->name = NULL;
	state->env = NULL;
}

/**
 * get_state - gets the state
 *
 * Return: pointer to the state
 */

struct State *get_state(void)
{
	if (state == NULL)
		init_state();

	return (state);
}

/**
 * free_state - frees the state
 */

void free_state(void)
{
	if (state == NULL)
		return;

	state->name = NULL;

	if (state->env != NULL)
		string_array_free(&state->env);

	free(state);
	state = NULL;
}
