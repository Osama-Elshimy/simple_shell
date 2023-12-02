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

	while (true)
	{
		char *line = NULL;
		char **tokens;

		line = get_line();
		tokens = tokenize(line);

		if (handle_command(tokens, envp) == -1)
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", argv[0]);

		free(line);
	}

	return (0);
}
