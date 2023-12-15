#include "shell.h"

/**
 * _myExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myExit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _Erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_Error(info, "Illegal number: ");
			_ePuts(info->argv[1]);
			_ePutchar('\n');
			return (1);
		}
		info->err_num = _Erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _myCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myCd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getEnv(info, "HOME=");
		chdir_ret = dir ? chdir(dir) : chdir((dir = _getEnv(info, "PWD="))
				? dir : "/");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getEnv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = (dir = _getenv(info, "OLDPWD=")) ? chdir(dir) : chdir("/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_Error(info, "can't cd to ");
		_ePuts(info->argv[1]), _ePutchar('\n');
	}
	else
	{
		_setEnv(info, "OLDPWD", _getEnv(info, "PWD="));
		_setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _myHelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myHelp(info_t *info)
{
	(void)info;
	_puts("help call works. Function not yet implemented \n");
	return (0);
}
