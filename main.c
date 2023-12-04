#include "main.h"

/**
 * main - entry point
 *
 * Description: a simple shell program
 *
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment vector
 *
 * Return: 0
 */

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	while (true)
	{
		char *line = NULL;
		char **commands = NULL;

		line = get_line();
		if (line == NULL)
			break;

		commands = parse_commands(line);
		handle_commands(commands, envp);

		string_array_free(&commands);
		free(line);
	}

	return (0);
}
