#include "shell.h"

/**
 * befree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int befree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	else if (ptr)
	{
		*ptr = NULL; /* Set pointer to NULL if it's already NULL */
	}
	return (0);
}

