#include "main.h"

/**
 * is_valid_env - checks if variable is valid
 *
 * @name: name of variable
 *
 * Return: 1 if valid else 0
 */

bool is_valid_env(const char *name)
{
	size_t i;

	if (name == NULL || isdigit(name[0]) || _strlen(name) == 0 ||
		strchr(name, '=') != NULL)
		return (false);

	for (i = 0; name[i] != '\0'; i++)
		if (!isalnum(name[i]) && name[i] != '_')
			return (false);

	return (true);
}

/**
 * get_env_index - gets the index of variable
 *
 * @name: name of variable
 *
 * Return: index of variable or -1
 */

int get_env_index(const char *name)
{
	char **env = get_state()->env;
	int name_len = _strlen(name);
	int i;

	if (env == NULL)
		return (-1);

	for (i = 0; env[i] != NULL; i++)
	{
		int env_len = (strchr(env[i], '=')) - env[i];

		if (env_len != name_len)
			continue;

		if (strncmp(env[i], name, name_len) == 0)
			return (i);
	}

	return (-1);
}

/**
 * assemble_env - assembles env variable
 *
 * @name: name of variable
 * @value: value of variable
 *
 * Return: assembled variable
 */

char *assemble_env(const char *name, const char *value)
{
	char *env = NULL;

	string_cat(&env, name);
	string_cat(&env, "=");
	string_cat(&env, value);

	return (env);
}
