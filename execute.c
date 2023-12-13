#include "main.h"

/**
 * is_path_accessible - checks if a path is accessible
 *
 * @path: the path to check
 *
 * Return: true if the path is accessible, false otherwise
 */

bool is_path_accessible(const char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && access(path, X_OK) == 0)
		return (true);

	return (false);
}

/**
 * is_dir - checks if a path is a directory
 *
 * @path: the path to check
 *
 * Return: true if the path is a directory, false otherwise
 */

bool is_dir(const char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (true);

	return (false);
}

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

	if ((command[0] == '/' || command[0] == '.') && is_path_accessible(command))
		return (strdup(command));

	path_env = strdup(get_env("PATH"));
	if (path_env == NULL)
		return (NULL);

	path = _strtok(path_env, ":");

	while (path)
	{
		path_copy = strdup(path);
		string_cat(&path_copy, "/");
		string_cat(&path_copy, command);

		if (is_path_accessible(path_copy))
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
 * Return: status
 */

int execute(char **argv)
{
	pid_t cpid;
	int status = 0;
	char *path = get_exec_path(argv[0]);

	if (path == NULL)
	{
		fprintf(stderr, "%s: %lu: %s: not found\n", get_state()->name,
				get_state()->count, argv[0]);
		return (127);
	}

	if (is_dir(path))
	{
		fprintf(stderr, "%s: %lu: %s: Permission denied\n", get_state()->name,
				get_state()->count, argv[0]);
		free(path);
		return (127);
	}

	cpid = fork();
	if (cpid == -1)
		perror("fork"), free(path), string_array_free(&argv), free_state(),
			exit(1);

	if (cpid == 0)
	{
		if (execve(path, argv, get_state()->env) == -1)
			perror("execve"), free(path), string_array_free(&argv),
				free_state(), exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		free(path);
	}
	return (status);
}
