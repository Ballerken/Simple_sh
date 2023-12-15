#include "shell.h"

/**
 * get_Environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: The string array copy of our environ.
 */
char **get_Environ(info_t *info)
{
	char **environ_copy = NULL;

	if (!info->environ || info->env_changed)
	{
		environ_copy = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (environ_copy);
}

/**
 * _unsetEnv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @var: The string env var property.
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetEnv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;
	int env_changed = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			env_changed = delete_node_at_INDEX(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	info->env_changed = env_changed;
	return (info->env_changed);
}

/**
 * _setEnv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */
int _setEnv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;
	int env_changed = 0;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_END(&(info->env), buf, 0);
	free(buf);
	info->env_changed = env_changed;
	return (0);
}
