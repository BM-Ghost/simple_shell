#include "shell.h"

/**
* _realloc_mem - Forcuses on the memory block
* @p: pointer
* @n_s: newsize
* @p_s: previous size
* Return: pointer
*/
void *_realloc_mem(void *p, unsigned int p_s, unsigned int n_s)
{
char *str, *ptr;
unsigned int i = 0;

ptr = (char *)p;

if (p == NULL)
return (malloc(n_s));
if (n_s == 0 && p != NULL)
{
free(p);
return (NULL);
}
if (n_s == p_s)
return (p);

str = malloc((n_s) * sizeof(char));

if (str == NULL)
{
free(str);
return (NULL);
}

do {
if (n_s > p_s)
str[i] = ptr[i];
else if (n_s < p_s)
str[i] = ptr[i];

i++;
} while (i < (n_s < p_s ? n_s : p_s));

free(ptr);
return (str);
}
