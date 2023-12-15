#include "shell.h"

/**
 * _myEnv - Prints the current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: (0) Always.
 */
int _myEnv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getEnv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getEnv(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node)
	{
		char *p = starts_with(node->str, name);

		if (p && *p)
			return (p);
		node = node->next;
	}

	return (NULL);
}

/**
 * _mysetEnv - Initializes a new environment variable or
 * modifies an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: (0) on success, (1) on failure.
 */
int _mysetEnv(info_t *info)
{
	if (info->argc != 3)
	{
		_ePuts("Incorrect number of arguments\n");
		return (1);
	}

	if (_setEnv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetEnv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: (0) Always.
 */
int _myunsetEnv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_ePuts("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
		_unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * populate_Env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: (0) Always.
 */
int populate_Env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);

	info->env = node;
	return (0);
}
