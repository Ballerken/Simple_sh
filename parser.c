#include "shell.h"

/**
 * is_Cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_Cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * create_path - creates a new path by concatenating directory and command
 * @dir: directory path
 * @cmd: command
 *
 * Return: pointer to new buffer or NULL
 */
char *create_path(const char *dir, const char *cmd)
{
	size_t dir_len = strlen(dir);
	size_t cmd_len = strlen(cmd);

	char *path = malloc(dir_len + cmd_len + 2);

	if (!path)
		return (NULL);

	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, cmd);

	return (path);
}

/**
 * find_path - finds the command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int curr_pos = 0;
	int a = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if (strlen(cmd) > 2 && starts_with(cmd, "./"))
	{
		if (is_Cmd(info, cmd))
			return (cmd);
	}

	while (pathstr[a] != '\0')
	{
		if (pathstr[a] == ':')
		{
			path = create_path(&pathstr[curr_pos], cmd);

			if (path)
			{
				if (is_Cmd(info, path))
					return (path);
				free(path);
			}
			curr_pos = a + 1;
		}
		a++;
	}
	path = create_path(&pathstr[curr_pos], cmd);

	if (path)
	{
		if (is_Cmd(info, path))
			return (path);
		free(path);
	}
	return (NULL);
}

