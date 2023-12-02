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
		return (strdup(command));

	path_env = strdup(getenv("PATH"));
	if (path_env == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	path = strtok(path_env, ":");

	while (path)
	{
		path_copy = strdup(path);
		cat_string(&path_copy, "/");
		cat_string(&path_copy, command);

		if (access(path_copy, X_OK) == 0)
		{
			free(path_env);
			return (path_copy);
		}

		free(path_copy);
		path = strtok(NULL, ":");
	}

	free(path_env);
	return (NULL);
}
