#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * if_del - checks if character is a delimiter
 * @c: the char to check
 * @del: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int if_del(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 * if_alpha - checks for alphabetic character
 * @ch: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int if_alpha(int ch)
{
return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, data = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			data *= 10;
			data += (s[i] - '0');
		}
		else if (data != 0)
			break;
	}

	return (sign * data);
}

