#include "main.h"

/**
 * exit_builtin - exits the shell
 *
 * @argv: argument vector
 */

void exit_builtin(char **argv)
{
	string_array_free(&argv);
	exit(0);
}
