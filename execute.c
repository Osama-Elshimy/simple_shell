#include "main.h"

/**
 * execute - executes a command and its arguments
 *
 * @argv: argument vector
 * @envp: environment vector
 *
 * Return: 0 on success, otherwise -1
 */

int execute(char **argv, char **envp)
{
	pid_t cpid;
	int status;
	char *path = get_exec_path(argv[0]);

	if (path == NULL)
	{
		string_array_free(&argv);
		free(path);
		return (-1);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		string_array_free(&argv);
		free(path);
		return (-1);
	}

	if (cpid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			perror("execve");
			string_array_free(&argv);
			free(path);
			return (-1);
		}
	}
	else
	{
		wait(&status);
		string_array_free(&argv);
		free(path);
	}

	return (0);
}
