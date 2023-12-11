#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void free_cmds(char **cmds);
char **tokenize(char *str, const char *delim);
void get_cmd_path(char **command);
extern char **environ;

int execute_command(char **commands, char *argv[], size_t cmd_count);
int check_executable(char **command);
void print_command_not_found(char **commands, char *argv[], size_t cmd_count);


#endif
