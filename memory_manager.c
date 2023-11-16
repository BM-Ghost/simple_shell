#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the memory block to reallocate
 * @old_size: Previous size of the memory block
 * @new_size: New size of the memory block
 *
 * Return: Pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size) {
    void *result;

    if (new_size == old_size)
        return ptr;

    if (new_size == 0 && ptr) {
        free(ptr);
        return NULL;
    }

    result = malloc(new_size);
    if (result == NULL)
        return NULL;

    if (ptr == NULL) {
        memset(result, 0, new_size); // Use memset to fill with zeros
        return result;
    }

    memcpy(result, ptr, old_size); // Use memcpy for byte copying
    free(ptr);
    return result;
}

/**
 * free_all - Frees memory allocated for an array of char pointers and a char pointer
 * @cmd: Array of char pointers to be freed
 * @line: Char pointer to be freed
 *
 * Return: Void
 */
void free_all(char **cmd, char *line) {
    free(cmd);
    free(line);
}

/**
 * _memcpy - Copies bytes from source to destination
 * @dest: Destination pointer
 * @src: Source pointer
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination
 */
char *_memcpy(char *dest, const char *src, unsigned int n) {
    unsigned int i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];

    return dest;
}

/**
 * fill_an_array - Fills an array with a constant byte
 * @a: Pointer to the array to be filled
 * @el: Value to fill the array with
 * @len: Length of the array
 *
 * Return: Pointer to the filled array
 */
void *fill_an_array(void *a, int el, unsigned int len) {
    unsigned char *p = a; // Use unsigned char pointer for byte-wise assignment
    unsigned int i;

    for (i = 0; i < len; i++)
        p[i] = (unsigned char)el;

    return a;
}

/**
 * _calloc - Allocates memory for an array and initializes it to zero
 * @size: Number of elements to allocate
 * Return: Pointer to the allocated memory; NULL if allocation fails
 */
void *_calloc(unsigned int size) {
    void *ptr;

    if (size == 0)
        return NULL;

    ptr = malloc(size);
    if (ptr != NULL) {
        // Use memset to initialize memory to zero
        memset(ptr, 0, size);
    }

    return ptr;
}

