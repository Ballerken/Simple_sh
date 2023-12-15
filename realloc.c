#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@m: the byte to fill *s with
 *@i: the amount of bytes to be filled
 *Return: a pointer to the memory area s
 */
char *_memset(char *a, char m, unsigned int i)
{
	unsigned int n;

	for (n = 0; n < i; n++)
		a[n] = m;
	return (a);
}

/**
 * freee - frees a string of strings
 * @pp: string of strings
 */
void freee(char **pp)
{
	char **m = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(m);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @curr_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int curr_size)
{
	char *p;

	if (!ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(ptr), NULL);
	if (curr_size == prev_size)
		return (ptr);

	p = malloc(curr_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}

