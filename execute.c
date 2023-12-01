#include "main.h"

/**
 * execute - executes a command and its arguments
 *
 * @tokens: array of tokens
 * @envp: array of environment variables
 * @name: name of shell
 */

void execute(char *tokens[], char *envp[], __attribute__((unused)) char *name)
{
	pid_t cpid;
	int status;
	char *full_path = get_full_path(tokens[0], envp);

	if (strcmp(tokens[0], "exit") == 0)
	{
		free_tokens(tokens);
		exit(0);
	}

	if (full_path != NULL)
	{
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			free_tokens(tokens);
			free(full_path);
			return;
		}

		if (cpid == 0)
		{
			if (execve(full_path, tokens, envp) == -1)
			{
				perror(full_path);
				free_tokens(tokens);
				exit(127);
			}
		}
		else
		{
			wait(&status);
			free_tokens(tokens);
			free(full_path);
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found: %s\n", name, tokens[0]);
		free_tokens(tokens);
	}
}
