#include "main.h"

void get_cmd_path(char **command);
void free_cmds(char **cmds);
char **tokenize(char *str, const char *delim);

/*
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

        get_cmd_path(&commands[0]);

        status = execute_command(commands, argv, cmd_count);

        free(lineptr);
        free_cmds(commands);
        commands = NULL;
        lineptr = NULL;
    }

    return 0;
}
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

void free_cmds(char **cmds)
{
    size_t i;

    for (i = 0; cmds[i] != NULL; i++)
    {
        free(cmds[i]);
        cmds[i] = NULL;
    }
    free(cmds);
}

char **tokenize(char *str, const char *delim)
{
    char **commands = NULL, *token, *dup_str;
    size_t num_of_tokens, i;

    if (str == NULL || *str == '\0')
        return (NULL);

    dup_str = strdup(str);
    token = strtok(dup_str, delim);

    num_of_tokens = 0;
    while (token != NULL)
    {
        ++num_of_tokens;
        token = strtok(NULL, delim);
    }
    free(dup_str);

    if (num_of_tokens > 0)
    {
        commands = malloc(sizeof(char *) * (num_of_tokens + 1));
        if (commands == NULL)
            exit(EXIT_FAILURE);

        token = strtok(str, delim);
        i = 0;
        while (token != NULL)
        {
            commands[i++] = strdup(token);
            token = strtok(NULL, delim);
        }
        commands[i] = NULL;
    }

    return (commands);
}

