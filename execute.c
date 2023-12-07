#include "main.h"

/**
 * get_exec_path - gets the full path of a command
 *
 * @command: the command
 *
 * Return: the full path of the command
 */

char *get_exec_path(const char *command)
{
	char *path_env = NULL;
	char *path = NULL;
	char *path_copy = NULL;

	if (access(command, X_OK) == 0)
		return (_strdup(command));

	path_env = _strdup(get_env("PATH"));
	if (path_env == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	path = _strtok(path_env, ":");

	while (path)
	{
		path_copy = _strdup(path);
		string_cat(&path_copy, "/");
		string_cat(&path_copy, command);

		if (access(path_copy, X_OK) == 0)
		{
			free(path_env);
			return (path_copy);
		}

		free(path_copy);
		path = _strtok(NULL, ":");
	}

	free(path_env);
	return (NULL);
}

/**
 * execute - executes a command and its arguments
 *
 * @argv: argument vector
 *
 * Return: 0 on success, otherwise -1
 */

int execute(char **argv)
{
	pid_t cpid;
	int status;
	char *path = get_exec_path(argv[0]);

	if (path == NULL)
	{
		free(path);
		return (-1);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		free(path);
		return (-1);
	}

	if (cpid == 0)
	{
		if (execve(path, argv, get_state()->env) == -1)
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
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status);
		free(path);
	}

	return (status);
}
