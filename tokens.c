#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
        int i, j, k, m, num_words = 0;
        char **c;

        if (str == NULL || str[0] == 0)
                return (NULL);
        if (!d)
                d = " ";
        for (i = 0; str[i] != '\0'; i++)
                if (!if_del(str[i], d) && (if_del(str[i + 1], d) || !str[i + 1]))
                        num_words++;

        if (num_words == 0)
                return (NULL);
        c = malloc((1 + num_words) * sizeof(char *));
        if (!c)
                return (NULL);
        for (i = 0, j = 0; j < num_words; j++)
        {
                while (if_del(str[i], d))
                        i++;
                k = 0;
                while (!if_del(str[i + k], d) && str[i + k])
                        k++;
                c[j] = malloc((k + 1) * sizeof(char));
                if (!c[j])
                {
                        for (k = 0; k < j; k++)
                                free(c[k]);
                        free(c);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        c[j][m] = str[i++];
                c[j][m] = 0;
        }
        c[j] = NULL;
        return (c);
}


/**
 * **strtoow - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtoow(char *str, char d)
{
	int i, j, k, m, num_words = 0; // Changed variable name from numwords to num_words
	char **c; // Changed variable name from s to c

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++; // Changed variable name from numwords to num_words
	if (num_words == 0)
		return (NULL);
	c = malloc((1 + num_words) * sizeof(char *)); // Changed variable name from s to c
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = str[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}

