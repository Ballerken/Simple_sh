#include "shell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int f = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(f)
		: "r"(f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_ePuts(av[0]);
				_ePuts(": 0: Can't open ");
				_ePuts(av[1]);
				_ePutchar('\n');
				_ePutchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = f;
	}

	populate_Env_list(info);
	read_History(info);
	hsh(info, av);

	return (EXIT_SUCCESS);
}
