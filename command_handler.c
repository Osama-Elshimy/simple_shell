#include "main.h"

static int status;

/**
 * handle_commands - handles multiple commands
 *
 * @commands: array of commands
 */

void handle_commands(char **commands)
{
	if (commands == NULL)
		return;

	while (*commands)
	{
		char **argv;

		if (is_operator(*commands))
		{
			handle_operator(&commands, status);
			continue;
		}

		argv = tokenize(*commands);
		status = handle_command(argv);
		if (status == -1)
			dprintf(STDERR_FILENO, "%s: No such file or directory\n",
					get_state()->name);

		commands++;
		string_array_free(&argv);
	}
}

/**
 * handle_command - handles command
 *
 * @argv: argument vector
 *
 * Return: status of command, or -1 if command is not found
 */

int handle_command(char **argv)
{
	if (argv == NULL)
		return (-1);

	if (_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	else if (_strcmp(argv[0], "env") == 0)
		return (builtin_env());
	else if (_strcmp(argv[0], "setenv") == 0)
		return (builtin_setenv(argv));
	else if (_strcmp(argv[0], "unsetenv") == 0)
		return (builtin_unsetenv(argv));
	else if (_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv));
	else
		return (execute(argv));
}
