#include "shell.h"

/**
 * putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * printErr - Display Error Based on Command and How Many Time Shell Looped
 * @input:User Input
 * @counter:Simple Shell Count Loop
 * @argv:Program Name
 * Return: Void
 */
void printErr(char *input, int counter, char **argv)
{
	char *er;

	PRINTER(argv[0]);
	PRINTER(": ");
	er = _itoa(counter);
	PRINTER(er);
	free(er);
	PRINTER(": ");
	PRINTER(input);
	PRINTER(": not found\n");
}

