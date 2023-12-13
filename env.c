#include "main.h"

/**
 * get_env - gets value of env variable
 *
 * @name: name of variable
 *
 * Return: value
 */

char *get_env(const char *name)
{
	char **env = get_state()->env;
	int env_index;

	if (name == NULL || *name == '\0')
		return (NULL);

	env_index = get_env_index(name);
	if (env_index == -1)
		return (NULL);

	return (strchr(env[env_index], '=') + 1);
}

/**
 * set_env - sets env variable
 *
 * @name: name of variable
 * @value: value of variable
 *
 * Return: 0 on success, otherwise -1
 */

int set_env(const char *name, const char *value)
{
	char **env = get_state()->env;
	int env_index;
	char *new_env;

	if (!is_valid_env(name) || value == NULL)
		return (-1);

	new_env = assemble_env(name, value);
	env_index = get_env_index(name);

	if (env_index != -1)
	{
		free(env[env_index]);
		env[env_index] = new_env;
		return (0);
	}

	string_array_push(&get_state()->env, new_env);
	free(new_env);
	return (0);
}

/**
 * unset_env - removes env variable
 *
 * @name: name of variable
 *
 * Return: 0 on success, otherwise -1
 */

int unset_env(const char *name)
{
	int env_index = get_env_index(name);

	if (!is_valid_env(name))
		return (-1);

	if (env_index == -1)
		return (0);

	string_array_remove(&get_state()->env, env_index);
	return (0);
}
