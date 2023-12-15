#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function Prototypes */

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _ePuts(char *);
int _ePutchar(char);
int _Putfd(char c, int fd);
int _Putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit_log.c */
char *_strnCpy(char *, char *, int);
char *_strnCat(char *, char *, int);
char *_strChr(char *, char);

/* tokens.c */
char **strtow(char *, char *);
char **strtoow(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void freee(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int befree(void **);

/* atoi.c */
int interactive(info_t *);
int if_del(char, char *);
int if_alpha(int);
int _atoi(char *);

/* errors2.c */
int _Erratoi(char *);
void print_Error(info_t *, char *);
int print_D(int, int);
char *convert_Number(long int, int, int);
void remove_Comments(char *);

/* builtin.c done */
int _myExit(info_t *);
int _myCd(info_t *);
int _myHelp(info_t *);

/* builtin1.c done */
int my_History(info_t *);
int _myAlias(info_t *);
int unset_Alias(info_t *info, char *str);
int set_Alias(info_t *info, char *str);
int print_Alias(list_t *node);

/* getline.c */
ssize_t get_Input(info_t *);
int _getLine(info_t *, char **, size_t *);
void siginthandler(int);
ssize_t input_Buf(info_t *info, char **buf, size_t *len);
ssize_t read_Buf(info_t *info, char *buf, size_t *i);

/* getinfo.c */
void clear_Info(info_t *);
void set_Info(info_t *, char **);
void free_Info(info_t *, int);

/* environiment.c */
char *_getEnv(info_t *, const char *);
int _myEnv(info_t *);
int _mysetEnv(info_t *);
int _myunsetEnv(info_t *);
int populate_Env_list(info_t *);

/* getenv.c */
char **get_Environ(info_t *);
int _unsetEnv(info_t *, char *);
int _setEnv(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c */
list_t *add_NODE(list_t **, const char *, int);
list_t *add_node_END(list_t **, const char *, int);
size_t print_list_STR(const list_t *);
int delete_node_at_INDEX(list_t **, unsigned int);
void free_LIST(list_t **);

/* lists1.c */
size_t listlen(const list_t *);
char **list_to_strings(list_t *);
size_t printlist(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int ischain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int replacealias(info_t *);
int replacevars(info_t *);
int replace_string(char **, char *);

#endif /* _MAIN_H_ */

