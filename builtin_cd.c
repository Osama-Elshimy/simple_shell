#include "main.h"

#define CD_BUFFER_SIZE 1024

/**
 * change_dir - changes the current working directory
 *
 * @new_dir: the directory to change to
 *
 * Return: status
 */

static int change_dir(char *new_dir)
{
	char current_dir[CD_BUFFER_SIZE];

	if (getcwd(current_dir, CD_BUFFER_SIZE) == NULL)
	{
		perror("getcwd");
		return (1);
	}

	if (new_dir == NULL)
		new_dir = current_dir;

	if (chdir(new_dir) == -1)
	{
		fprintf(stderr, "%s: %lu: cd: can't cd to %s\n", get_state()->name,
				get_state()->count, new_dir);
		return (2);
	}

	set_env("PWD", new_dir);
	set_env("OLDPWD", current_dir);

	return (0);
}

/**
 * cd_old_dir - changes the current directory to $OLDPWD
 *
 * Return: status
 */

static int cd_old_dir(void)
{
	char *old_dir = get_env("OLDPWD");

	if (old_dir == NULL)
	{
		char current_dir[CD_BUFFER_SIZE];

		if (getcwd(current_dir, CD_BUFFER_SIZE) == NULL)
		{
			perror("getcwd");
			return (1);
		}

		printf("%s\n", current_dir);
	}
	else
		printf("%s\n", old_dir);

	return (change_dir(old_dir));
}

/**
 * builtin_cd - changes the current directory
 *
 * @argv: argument vector
 *
 * Return: status
 */

int builtin_cd(char **argv)
{
	if (argv[1] == NULL)
		return (change_dir(get_env("HOME")));
	else if (strcmp(argv[1], "-") == 0)
		return (cd_old_dir());
	else
		return (change_dir(argv[1]));
}
