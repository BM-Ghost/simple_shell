#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @av: Array of strings containing command arguments (unused)
 * @input: Input string (unused)
 * @exiti: Exit status pointer (unused)
 *
 * Return: Always returns 1 (true)
 */

int print_env(char **av, char *input, int *exiti)
{
int  i;

i = 0;

(void)av;
(void)input;
(void)exiti;

if (environ[i] == NULL)
{
printf("%s", "Built environment empty!");
return (1);
}

do {
printf("%s\n", environ[i]);
i++;
} while (environ[i]);

return (1);
}
