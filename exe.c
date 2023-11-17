#include "shell.h"

/**
 * _exe_builtin - Executes built-in commands
 * @a: Command arguments
 * @user_input: Original input string
 * @args: Array of command arguments
 * @exit_status: Pointer to the exit status
 *
 * Return: 0 on success, -1 on failure
 */

int _exe_builtin(char **a, char *user_input , char **args, int *exit_status )
{
int i;

choice_t choices[] = {
{"exit", exit_cmd},
{"en", print_env},
{"cd", curr_dir},
{"setenv", set_env},
{"unsetenv", unset_env},
{NULL, NULL}
};

i = 0;

while (choices[i].naming_built)
{
if (strcmp(choices[i].naming_built, a[0]) == 0)

return ((int)((*choices[i].fun_built)(a, user_input , exit_status )));

i++;
}

return (exe_cmd(a, args, exit_status ));
}
