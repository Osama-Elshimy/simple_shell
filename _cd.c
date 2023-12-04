#include "main.h"

/**
 * change_dir - changes the current working directory
 *
 * @new_dir: the directory to change to
 *
 * Return: void
 */

void change_dir(char *new_dir)
{
	char *current_dir = getcwd(NULL, 0);

	if (current_dir == NULL)
	{
		perror("getcwd");
		return;
	}

	if (setenv("OLDPWD", current_dir, 1) != 0)
		perror("setenv");

	else if (chdir(new_dir) != 0)
		perror("chdir");

	else if (setenv("PWD", new_dir, 1) != 0)
		perror("setenv");

	/*
	 * free(current_dir);
	 */
}

/**
 * cd_home - changes the current directory to $HOME
 *
 * Return: void
 */

void cd_home(void)
{
	char *new_dir = getenv("HOME");

	if (new_dir == NULL)
	{
		fprintf(stderr, "cd: $HOME not set\n");
		return;
	}

	change_dir(new_dir);
}

/**
 * cd_old_dir - changes the current directory to $OLDPWD
 *
 * Return: void
 */

void cd_old_dir(void)
{
	char *new_dir = getenv("OLDPWD");

	if (new_dir == NULL)
	{
		fprintf(stderr, "cd: $OLDPWD not set\n");
		return;
	}

	change_dir(new_dir);
}

/**
 * cd_args - changes the current directory to the argument
 *
 * @argv: argument vector
 *
 * Return: void
 */

void cd_args(char **argv)
{
	char *new_dir = argv[1];

	change_dir(new_dir);
}

/**
 * _cd - changes the current directory
 *
 * @argv: argument vector
 *
 * Return: void
 */

void _cd(char **argv)
{
	if (argv[1] == NULL)
		cd_home();
	else if (strcmp(argv[1], "-") == 0)
		cd_old_dir();
	else
		cd_args(argv);
}
