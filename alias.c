#include "main.h"
#include <stdio.h>

static struct Alias **aliases;

/**
 * get_aliases_length - returns the length of the aliases array
 *
 * Return: the length of the aliases array
 */

int get_aliases_length(void)
{
	int i = 0;

	while (aliases && aliases[i])
		i++;

	return (i);
}

/**
 * get_alias - returns the value of an alias
 *
 * @alias_name: the name of the alias
 *
 * Return: the value of the alias
 */

char *get_alias(char *alias_name)
{
	int i;
	int len = get_aliases_length();

	for (i = 0; i < len; i++)
		if (aliases[i]->name && _strcmp(aliases[i]->name, alias_name) == 0)
			return (aliases[i]->value);

	fprintf(stderr, "alias: command not found");
	return (NULL);
}

/**
 * allocate_alias - allocates memory for a new alias
 *
 * @name: the name of the alias
 * @value: the value of the alias
 *
 * Return: a pointer to the newly allocated alias or NULL on failure
 */

static struct Alias *allocate_alias(char *name, char *value)
{
	struct Alias *new_alias = malloc(sizeof(struct Alias));

	if (!new_alias)
	{
		perror("malloc");
		return (NULL);
	}

	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);

	if (!new_alias->name || !new_alias->value)
	{
		perror("strdup");
		free(new_alias->name);
		free(new_alias->value);
		free(new_alias);
		return (NULL);
	}

	return (new_alias);
}

/**
 * set_alias - sets an alias
 *
 * @name: the name of the alias
 * @value: the value of the alias
 *
 * Return: 0 on success, -1 on failure
 */

int set_alias(char *name, char *value)
{
	int i, len;
	struct Alias *new_alias;

	if (!name || !value)
	{
		perror("name or value is NULL");
		return (-1);
	}

	len = get_aliases_length();
	for (i = 0; i < len; i++)
	{
		if (_strcmp(name, aliases[i]->name) == 0)
		{
			free(aliases[i]->value);
			aliases[i]->value = _strdup(value);
			return (0);
		}
	}

	new_alias = allocate_alias(name, value);
	if (!new_alias)
		return (-1);

	aliases = _realloc(aliases, sizeof(struct Alias *) * (len + 2));

	if (!aliases)
	{
		perror("realloc");
		free(new_alias->name);
		free(new_alias->value);
		free(new_alias);
		return (-1);
	}

	aliases[len] = new_alias;
	aliases[len + 1] = NULL;

	return (0);
}

/**
 * free_aliases - frees the memory allocated for the aliases
 *
 * Return: void
 */

void free_aliases(void)
{
	int i;
	int len = get_aliases_length();

	for (i = 0; i < len; i++)
	{
		free(aliases[i]->name);
		free(aliases[i]->value);
		free(aliases[i]);
	}

	free(aliases);
	aliases = NULL;
}
