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
	state->prompt = NULL;
	state->fd = -1;
	state->status = 0;
	state->count = 0;
	state->env = NULL;
	state->aliases = NULL;
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
	state->prompt = NULL;
	state->fd = -1;
	state->status = 0;
	state->count = 0;

	if (state->env != NULL)
		string_array_free(&state->env);

	if (state->aliases != NULL)
		string_array_free(&state->aliases);

	free(state);
	state = NULL;
}
