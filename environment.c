#include "shell.h"

/**
 * unset_env - Removes a specified environment variable
 * @av: Array of strings containing command arguments
 * @input: Input string (unused)
 * @exiti: Exit status pointer (unused)
 * Return: 1 on success, 0 on failure
 */
int unset_env(char **av, char *input, int *exiti)
{
    int number_tokens = 0;

    (void)input;
    (void)exiti;

    while (av[number_tokens] != NULL)
    {
        number_tokens++;
    }

    if (number_tokens == 2)
        unsetenv(av[1]);
    else
        fprintf(stderr, "Try 'setenvironment' key value\n");
    
    return 1;
}

/**
 * set_env - Sets or overwrites an environment variable
 * @av: Array of strings containing command arguments
 * @input: Input string (unused)
 * @exiti: Exit status pointer (unused)
 * Return: 1 on success, 0 on failure
 */
int set_env(char **av, char *input, int *exiti)
{
    int number_tokens = 0;

    (void)input;
    (void)exiti;

    while (av[number_tokens] != NULL)
    {
        number_tokens++;
    }

    if (number_tokens == 3)
        setenv(av[1], av[2], 1);
    else if (number_tokens < 3)
        fprintf(stderr, "Try 'setenvironment' key value\n");
    else
        fprintf(stderr, "Try 'setenvironment' key value\n");

    return 1;
}
