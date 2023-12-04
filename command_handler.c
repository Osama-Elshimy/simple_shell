#include "main.h"

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
	if (strcmp(argv[0], "exit") == 0)
	{
		exit_builtin(argv);
		return (0);
	}
	else if (strcmp(argv[0], "setenv") == 0)
	{
		_setenv(argv);
		return (0);
	}
	else if (strcmp(argv[0], "unsetenv") == 0)
	{
		_unsetenv(argv);
		return (0);
	}
	else if (strcmp(argv[0], "cd") == 0)
	{
		_cd(argv);
		return (0);
	}

	return (execute(argv, envp));
}
