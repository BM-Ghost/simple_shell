#include “shell.h”

/**
 * _strncpy - Custom implementation to copy a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The maximum number of characters to be copied
 *
 * Return: Pointer to the copied string (destination)
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';

    return dest;
}

/**
 * _strncat - Custom implementation to concatenate two strings
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of bytes to be concatenated
 *
 * Return: Pointer to the concatenated string (destination)
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}

/**
 * _strchr - Custom implementation to locate a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 *
 * Return: Pointer to the first occurrence of the character 'c' in 's', or NULL if not found
 */
char *_strchr(const char *s, int c)
{
    while (*s != (char)c)
    {
        if (*s == '\0')
            return NULL;
        s++;
    }

    return (char *)s;
}
