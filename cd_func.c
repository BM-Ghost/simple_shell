#include "shell.h"

/**
 * curr_dir - Changes the current working directory
 * @av: Array of strings containing command arguments
 * @input: Input string (unused in this function)
 * @exiti: Exit status pointer (unused in this function)
 * Return: 1 if successful, otherwise returns -1
 */

int curr_dir(char **av, char *input, int *exiti)
{
int stat;

char str[128];

(void)input;
(void)exiti;

if (av[1] == NULL)
stat = chdir(fetch_env("HOME"));
else if (strcmp(av[1], "-") == 0)
stat = chdir(fetch_env("OLDPWD"));
else if (strcmp(av[1], "~") == 0)
stat = chdir(fetch_env("HOME"));
else
stat  = chdir(av[1]);

if (stat == -1)
perror("There is an error in the cd");

setenv("OLDPWD", str, 1);
setenv("PWD", getcwd(str, sizeof(str)), 1);
return (1);
}
