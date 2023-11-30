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
		free(line);
		if (!tokens)
			continue;

		execute(tokens, envp, argv[0]);
	}

	return (0);
}
