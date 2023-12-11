#include "main.h"

int execute_command(char **commands, char *argv[], size_t cmd_count);
int check_executable(char **command);
void print_command_not_found(char **commands, char *argv[], size_t cmd_count);

int main(__attribute__((unused))int argc, char *argv[])
{
	char *lineptr = NULL, **commands = NULL;
	size_t n = 0, cmd_count = 0;
	ssize_t n_read;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		fflush(stdout);
		n_read = getline(&lineptr, &n, stdin);
		++cmd_count;

		if (n_read == -1)
		{
			free(lineptr);
			lineptr = NULL;
			if (isatty(STDIN_FILENO))
				printf("\n");

			exit(0);
		}

		lineptr[n_read - 1] = '\0';

		if (*lineptr == '\0')
			continue;

		commands = tokenize(lineptr, " ");
		if (commands == NULL)
			continue;

		if (check_executable(&commands[0]) == -1)
		{
			print_command_not_found(commands, argv, cmd_count);
			free_cmds(commands);
			continue;
		}

		status = execute_command(commands, argv, cmd_count);

		free(lineptr);
		free_cmds(commands);
		commands = NULL;
		lineptr = NULL;
	}

	return (0);
}

int execute_command(char **commands, char *argv[], size_t cmd_count)
{
	pid_t child = fork();
	int status;

	if (child == -1)
		return (-1);

	if (child == 0)
	{
		if (execve(commands[0], commands, environ) == -1)
			perror("execve");
	}
	else
	{
		waitpid(child, &status, 0);
	}

	return (status);
}

int check_executable(char **command)
{
	if (access(*command, X_OK) == -1)
	{
		get_cmd_path(command);

		if (*command != NULL && access(*command, X_OK) == -1)
			return (-1);
	}

	return (0);
}

void print_command_not_found(char **commands, char *argv[], size_t cmd_count)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", argv[0], cmd_count, commands[0]);
}

/**
 * get_cmd_path - Gets the full path to a command if it's valid and exists in
 *                the PATH list of directories.
 * @command: A pointer to the string containing the command to get the full path for.
 *
 * Note: The string is modified in place, and it is recommended to pass the
 *       address of the string.
 */

void get_cmd_path(char **command)
{
    char *dir = NULL, *path = NULL, *path_dir, *dup_str;

    if (*command == NULL || command == NULL)
        return;

    path_dir = getenv("PATH");
    if (path_dir == NULL)
        return;

    dup_str = strdup(path_dir);
    dir = strtok(dup_str, ":");

    while (dir != NULL)
    {
        path = malloc(sizeof(char) * (strlen(*command) + strlen(dir) + 2));
        if (path == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }

        sprintf(path, "%s/%s", dir, *command);

        if (access(path, X_OK) == 0)
        {
            free(*command);
            *command = strdup(path);
            free(path);
            break;
        }

        free(path);
        dir = strtok(NULL, ":");
    }
    free(dup_str);
}
