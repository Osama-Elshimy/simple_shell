#include "main.h"

/**
 * get_alias - gets value of an alias
 *
 * @name: name of alias
 *
 * Return: value
 */

char *get_alias(const char *name)
{
	char **aliases = get_state()->aliases;
	int alias_index;

	if (name == NULL || *name == '\0')
		return (NULL);

	alias_index = get_alias_index(name);

	if (alias_index == -1)
		return (NULL);

	return (strchr(aliases[alias_index], '=') + 1);
}

/**
 * set_alias - sets alias
 *
 * @name: name of alias
 * @value: value of alias
 *
 * Return: 0 on success, otherwise -1
 */

int set_alias(const char *name, const char *value)
{
	char **aliases = get_state()->aliases;
	int alias_index;
	char *new_alias;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);

	alias_index = get_alias_index(name);
	new_alias = assemble_alias(name, value);

	if (alias_index != -1)
	{
		free(aliases[alias_index]);
		aliases[alias_index] = new_alias;
		return (0);
	}

	string_array_push(&get_state()->aliases, new_alias);
	free(new_alias);
	return (0);
}
