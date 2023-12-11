#include "main.h"

/**
 * get_alias_index - gets the index of alias
 *
 * @name: name of variable
 *
 * Return: index of alias or -1
 */

int get_alias_index(const char *name)
{
	char **aliases = get_state()->aliases;
	int name_len = _strlen(name);
	int i;

	if (aliases == NULL)
		return (-1);

	for (i = 0; aliases[i] != NULL; i++)
	{
		int alias_len = (strchr(aliases[i], '=')) - aliases[i];

		if (alias_len != name_len)
			continue;

		if (strncmp(aliases[i], name, name_len) == 0)
			return (i);
	}

	return (-1);
}

/**
 * assemble_alias - assembles alias value
 *
 * @name: name of alias
 * @value: value of alias
 *
 * Return: assembled alias
 */

char *assemble_alias(const char *name, const char *value)
{
	char *alias = NULL;

	string_cat(&alias, name);
	string_cat(&alias, "=");
	string_cat(&alias, value);

	return (alias);
}
