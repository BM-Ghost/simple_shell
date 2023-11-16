#include "shell.h"

/**
 * _errAtoi - Converts a string to an integer
 * @s: The string to be converted
 * Return: Converted number if successful, -1 on error
 */
int _errAtoi(char *s) {
	int result = 0;
    int sign = 1;
    if (s == NULL) {
        fprintf(stderr, "Error: NULL string\n");
        return -1;
    }
    if (*s == '+' || *s == ' ')
        s++;

    while (*s != '\0') {
        if (*s >= '0' && *s <= '9') {
            if (result > (INT_MAX / 10) || (result == (INT_MAX / 10) && (*s - '0') > (INT_MAX % 10))) {
                fprintf(stderr, "Error: Integer overflow\n");
                return -1;
            }
            result = result * 10 + (*s - '0');
        } else {
            fprintf(stderr, "Error: Invalid character in string\n");
            return -1;
        }
        s++;
    }
    return result * sign;
}

/**
 * printErr - Prints an error message
 * @info: The parameter & return info struct
 * @estr: String containing specified error message
 */
void printErr(FuncInfo *info, char *estr) {
    if (info == NULL || estr == NULL) {
        fprintf(stderr, "Error: NULL arguments\n");
        return;
    }
    _ePuts(info->fname);
    _ePuts(": ");
    printD(info->line_cnt, STDERR_FILENO);
    _ePuts(": ");
    _ePuts(info->argv[0]);
    _ePuts(": ");
    _ePuts(estr);
}

/**
 * printD - Prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 * Return: Number of characters printed, -1 on error
 */
int printD(int input, int fd) {
	unsigned int divisor = 1;
	int count = 0;
    unsigned int _abs_;

    if (fd != STDERR_FILENO && fd != STDOUT_FILENO) {
        fprintf(stderr, "Error: Invalid file descriptor\n");
        return -1;
    }
    if (input < 0) {
        _eputChar('-');
        _abs_ = -input;
        count++;
    } else {
        _abs_ = input;
    }
    while (_abs_ / divisor > 9)
        divisor *= 10;
    while (divisor != 0) {
        _eputChar((_abs_ / divisor) % 10 + '0');
        count++;
        divisor /= 10;
    }
    return count;
}

/**
 * convertNum - Converts a number into a string representation
 * @num: The number to be converted
 * @base: The base for conversion
 * @flags: Conversion flags
 *
 * Return: A string representation of the number
 */
char *convertNum(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr = &buffer[49];
	unsigned long n = num;
	static const char *array_lower = "0123456789abcdef";
	static const char *array_upper = "0123456789ABCDEF";
	const char *array = (flags & CONVERT_LOWERCASE) ? array_lower : array_upper;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return ptr;
}

/**
 * removeComments - Replaces the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 */
void removeComments(char *buf)
{
	if (buf == NULL)
		return;

	while (*buf != '\0')
	{
		if (*buf == '#' && (buf == buf || *(buf - 1) == ' '))
		{
			*buf = '\0';
			break;
		}
		buf++;
	}
}

