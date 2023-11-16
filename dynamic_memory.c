#include <stdlib.h>
#include "shell.h"

/**
 * freePtr - Frees a pointer and sets the address to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freePtr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return 1;
	}
	else
	{
		fprintf(stderr, "Error: Pointer is NULL\n");
		return 0;
	}
}
