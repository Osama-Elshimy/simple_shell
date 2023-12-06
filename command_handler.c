#include "main.h"

static int status;

/**
 * handle_commands - handles multiple commands
 *
 * @commands: array of commands
 * @envp: environment vector
 */

void handle_commands(char **commands, char **envp)
{
	if (commands == NULL || envp == NULL)
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
		status = handle_command(argv, envp);
		commands++;

		string_array_free(&argv);
	}
}

/**
 * handle_command - handles command
 *
 * @argv: argument vector
 * @envp: environment vector
 *
 * Return: 0 on success, otherwise -1
 */

int handle_command(char **argv, char **envp)
{
	if (argv == NULL || envp == NULL)
		return (-1);

	if (_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	else if (_strcmp(argv[0], "setenv") == 0)
		return (builtin_setenv(argv));
	else if (_strcmp(argv[0], "unsetenv") == 0)
		return (builtin_unsetenv(argv));
	else if (_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv));
	else
		return (execute(argv, envp));
}
