#include "main.h"

/**
 * execute - executes a command and its arguments
 *
 * @tokens: array of tokens
 * @envp: array of environment variables
 * @name: name of shell
 */

void execute(char *tokens[], char *envp[], char *name)
{
	pid_t cpid;
	int status;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		free_tokens(tokens);
		return;
	}

	if (cpid == 0)
	{
		if (execve(tokens[0], tokens, envp) == -1)
		{
			free_tokens(tokens);
			perror(tokens[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free_tokens(tokens);
	}
}
