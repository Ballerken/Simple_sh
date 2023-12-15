#include "shell.h"

/**
 * _ePuts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _ePuts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_ePutchar(str[i]);
		i++;
	}
}

/**
 * _ePutchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _ePutchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _Putfd - Writes the character c to the given fd.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _Putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _Putsfd - Prints an input string.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _Putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _Putfd(*str++, fd);
	}

	return (i);
}
