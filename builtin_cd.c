#include "main.h"

/**
 * change_dir - changes the current working directory
 *
 * @new_dir: the directory to change to
 *
 * Return: void
 */

static int change_dir(char *new_dir)
{
	char *current_dir = getcwd(NULL, 0);

	if (current_dir == NULL)
	{
		perror("getcwd");
		return (1);
	}

	if (chdir(new_dir) == 0)
	{
		if (setenv("OLDPWD", current_dir, 1) != 0)
			perror("setenv");

		if (setenv("PWD", new_dir, 1) != 0)
			perror("setenv");

		free(current_dir);
		return (0);
	}
	else
	{
		perror("cd");
		free(current_dir);
		return (1);
	}
}

/**
 * cd_home - changes the current directory to $HOME
 *
 * Return: void
 */

static int cd_home(void)
{
	char *new_dir = getenv("HOME");

	if (new_dir == NULL)
	{
		fprintf(stderr, "cd: $HOME not set\n");
		return (1);
	}

	return (change_dir(new_dir));
}

/**
 * cd_old_dir - changes the current directory to $OLDPWD
 *
 * Return: void
 */

static int cd_old_dir(void)
{
	char *new_dir = getenv("OLDPWD");

	if (new_dir == NULL)
	{
		fprintf(stderr, "cd: $OLDPWD not set\n");
		return (1);
	}

	return (change_dir(new_dir));
}

/**
 * cd_args - changes the current directory to the argument
 *
 * @argv: argument vector
 *
 * Return: void
 */

static int cd_args(char **argv)
{
	char *new_dir = argv[1];

	return (change_dir(new_dir));
}

/**
 * _cd - changes the current directory
 *
 * @argv: argument vector
 *
 * Return: void
 */

int builtin_cd(char **argv)
{
	if (argv[1] == NULL)
		return (cd_home());
	else if (strcmp(argv[1], "-") == 0)
		return (cd_old_dir());
	else
		return (cd_args(argv));
}
