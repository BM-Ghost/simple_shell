#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Function Prototypes */
void _ePuts(char *str);
int _eputChar(char c);
int _putFd(char c, int fd);
int _putsFd(char *str, int fd);

/**
 * _ePuts - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _ePuts(char *str)
{
	if (!str)
	{
		fprintf(stderr, "Error: _ePuts() called with NULL string\n");
		return;
	}

	while (*str)
	{
		_eputChar(*str++);
	}
}

/**
 * _eputChar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputChar(char c)
{
	static int buf_index = 0;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buf_index >= WRITE_BUFFER_SIZE - 1)
	{
		if (write(STDERR_FILENO, buf, buf_index) == -1)
			return -1;
		buf_index = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[buf_index++] = c;
	return 1;
}

/**
 * _putFd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putFd(char c, int fd)
{
	static int buf_index = 0;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buf_index >= WRITE_BUFFER_SIZE - 1)
	{
		if (write(fd, buf, buf_index) == -1)
			return -1;
		buf_index = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[buf_index++] = c;
	return 1;
}

/**
 *_putsFd - prints an input string to given fd
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsFd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
	{
		fprintf(stderr, "Error: _putsFd() called with NULL string\n");
		return 0;
	}
	while (*str)
	{
		char_count += _putFd(*str++, fd);
	}
	return char_count;
}
