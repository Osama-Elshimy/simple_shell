#include "main.h"

void handle_operator_and(char ***commands, int status)
{
	if (status == 0)
	{
		(*commands)++;
		return;
	}

	if (*((*commands) + 1) == NULL)
	{
		dprintf(STDERR_FILENO, "Syntax error\n");
		return;
	}

	(*commands) += 2;
}

void handle_operator_or(char ***commands, int status)
{
	if (status != 0)
	{
		(*commands)++;
		return;
	}

	if (*((*commands) + 1) == NULL)
	{
		dprintf(STDERR_FILENO, "Syntax error\n");
		return;
	}

	(*commands) += 2;
}

void handle_operator_semi(char ***commands)
{
	(*commands)++;
}

void handle_operator_hash(char ***commands)
{
	**commands = NULL;
}

void handle_operator(char ***commands, int status)
{
	enum Operator type = get_operator_type(**commands);

	if (is_operator(*(*commands + 1)))
	{
		dprintf(STDERR_FILENO, "Syntax error\n");
		**commands = NULL;
		return;
	}

	switch (type)
	{
		case AND:
			handle_operator_and(commands, status);
			break;
		case OR:
			handle_operator_or(commands, status);
			break;
		case SEMI:
			handle_operator_semi(commands);
			break;
		case HASH:
			handle_operator_hash(commands);
			break;
		case UNDEF:
			(*commands)++;
			dprintf(STDERR_FILENO, "Not implemented\n");
	}
}
