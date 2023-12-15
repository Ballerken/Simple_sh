#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtinrett = 0;

	while (r != -1 && builtinrett != -2)
	{
		clear_Info(info);
		if (interactive(info))
			_puts("$ ");
		_ePutchar(BUF_FLUSH);
		r = get_Input(info);
		if (r != -1)
		{
			set_Info(info, av);
			builtinrett = find_builtin(info);
			if (builtinrett == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_Info(info, 0);
	}
	write_History(info);
	free_Info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtinrett == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtinrett);
}


/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, builtin_rett = -1;
	builtin_table builtintbl[] = {
		{"exit", _myExit},
		{"env", _myEnv},
		{"help", _myHelp},
		{"history", my_History},
		{"setenv", _mysetEnv},
		{"unsetenv", _myunsetEnv},
		{"cd", _myCd},
		{"alias", _myAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_rett = builtintbl[i].func(info);
			break;
		}
	return (builtin_rett);
}


/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!if_del(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, _getEnv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getEnv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_Cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_Error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_Environ(info)) == -1)
		{
			free_Info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_Error(info, "Permission denied\n");
		}
	}
}

