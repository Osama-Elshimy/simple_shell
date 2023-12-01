#include "main.h"

/**
 * get_full_path - gets the full path of a command
 *
 * @command: the command
 * @envp: the environment variables
 *
 * Return: the full path of the command
 */

char *get_full_path(const char *command, __attribute__((unused)) char *envp[])
{
	char *path = getenv("PATH"), *path_copy, *token;

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set.\n");
		return (NULL);
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		char *full_path = malloc(strlen(token) + strlen(command) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
