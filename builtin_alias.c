#include "main.h"

/**
 * print_alias - prints an alias
 *
 * @name: alias name
 *
 * Return: true on success, false on failure
 */

static bool print_alias(char *name)
{
	char *alias = get_alias(name);

	if (alias == NULL)
	{
		fprintf(stderr, "alias: %s not found\n", name);
		return (false);
	}

	printf("%s='%s'\n", name, alias);
	return (true);
}

/**
 * print_aliases - prints all aliases
 */

static void print_aliases(void)
{
	char **aliases = get_state()->aliases;

	if (aliases == NULL)
		return;

	while (*aliases != NULL)
	{
		char *alias = strdup(*aliases);
		char *name = _strtok(alias, "=");

		print_alias(name);
		free(alias);
		aliases++;
	}
}

/**
 * builtin_alias - handles builtin alias
 *
 * @argv: argument vector
 *
 * Return: status
 */

int builtin_alias(char **argv)
{
	size_t argc = string_array_length(argv);
	size_t i;
	int status = 0;

	if (argc == 1)
	{
		print_aliases();
		return (0);
	}

	for (i = 1; i < argc; i++)
	{
		char *arg = strdup(argv[i]);
		char *eq = strchr(arg, '=');
		char *name = _strtok(arg, "=");
		char *value = _strtok(NULL, "=");

		if (eq == NULL)
		{
			if (!print_alias(name))
				status = 1;
			free(arg);
			continue;
		}

		set_alias(name, value);
		free(arg);
	}

	return (status);
}
