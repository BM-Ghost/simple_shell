#include "shell.h"

/**
 * exit_cmd - Exit command
 * @av: Array of strings containing command arguments
 * @input: Input string (unused)
 * @exiti: Exit status pointer
 * Return: Always returns 0
 */

int exit_cmd(char **av, char *input, int *exiti)
{
int exit_show;
exit_show = 0;

(void)av;
(void)input;
(void)exit;

if (av[1] == NULL)
{
free(av);
free(input);
exit(*exiti);
}

if (av[1] == NULL)
{
fprintf(stderr, "exit: Too many arguments here!\n");
return (0);
}

exit_show = atoi(av[1]);
free(av);
free(input);
exit(exit_show);
}
