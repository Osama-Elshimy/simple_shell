#include "main.h"

/**
 * handle_commands - handles multiple commands
 *
 * @commands: array of commands
 */

void handle_commands(char **commands)
{
	if (commands == NULL)
		return;

	while (*commands != NULL)
	{
		char **argv = NULL;

		if (is_operator(*commands))
		{
			handle_operator(&commands, get_state()->status);
			continue;
		}

		argv = parse_command(*commands);
		get_state()->status = handle_command(argv);

		commands++;
		string_array_free(&argv);
	}
}

/**
 * handle_command - handles command
 *
 * @argv: argument vector
 *
 * Return: status of command
 */

int handle_command(char **argv)
{
	int status = 0;

	get_state()->count++;

	if (argv == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		builtin_exit(argv);
	else if (strcmp(argv[0], "env") == 0)
		status = builtin_env();
	else if (strcmp(argv[0], "setenv") == 0)
		status = builtin_setenv(argv);
	else if (strcmp(argv[0], "unsetenv") == 0)
		status = builtin_unsetenv(argv);
	else if (strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv);
	else if (strcmp(argv[0], "alias") == 0)
		status = builtin_alias(argv);
	else
		status = execute(argv);

	return (status);
}
