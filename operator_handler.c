#include "main.h"

/**
 * handle_operator_and - handles && operator
 *
 * @commands: pointer to the array of commands
 * @status: status of the last command
 */

void handle_operator_and(char ***commands, int status)
{
	if (status == 0)
	{
		(*commands)++;
		return;
	}

	if (*((*commands) + 1) == NULL)
	{
		(*commands)++;
		return;
	}

	(*commands) += 2;
}

/**
 * handle_operator_or - handles || operator
 *
 * @commands: pointer to the array of commands
 * @status: status of the last command
 */

void handle_operator_or(char ***commands, int status)
{
	if (status != 0)
	{
		(*commands)++;
		return;
	}

	if (*((*commands) + 1) == NULL)
	{
		(*commands)++;
		return;
	}

	(*commands) += 2;
}

/**
 * handle_operator_semi - handles ; operator
 *
 * @commands: pointer to the array of commands
 */

void handle_operator_semi(char ***commands)
{
	(*commands)++;
}

/**
 * handle_operator - handles operators
 *
 * @commands: pointer to the array of commands
 * @status: status of the last command
 */

void handle_operator(char ***commands, int status)
{
	enum Operator type = get_operator_type(**commands);

	if (is_operator(*(*commands + 1)))
	{
		while (**commands != NULL)
			(*commands)++;
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
		case UNDEF:
			break;
	}
}
