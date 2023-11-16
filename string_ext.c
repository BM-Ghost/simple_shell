#include "shell.h"

/**
* strcpy - copies a string
* @dest: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
* strDup - duplicates a string
* @str: the string to duplicate
*
* Return: pointer to the duplicated string
*/
char *strDup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
* customPuts - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void customPuts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar(str[i]);
		i++;
	}
}
/**
* putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}
