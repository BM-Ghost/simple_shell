#include "shell.h"

/**
 * main - Shell entry point
 * @argc: Argument count
 * @argv: Array of arguments
 * Return: Always 0 (Success)
 */

int main(int arg __attribute__((unused)), char **argc  __attribute__((unused)))
{
char **args = NULL;
char *user_input  = NULL;
int tty_status  = 1;
int exit_status  = 0;


ssize_t read_status  = 0;
size_t input_size  = 0;

while (tty_status  && read_status  != EOF)
{
input_size  = 0;
tty_status  = isatty(STDIN_FILENO);

if (tty_status )
write(STDOUT_FILENO, "", 0);

signal(SIGINT, manage_signal);
read_status  = getline(&user_input , &input_size , stdin);
if (read_status  == -1)
{
free(user_input );
break;
}
if (space_ver(user_input ))
{
free(user_input );
continue;
}
args = _token_util(user_input );
if (*args[0] == '\0')
continue;
tty_status  = _exe_builtin(args, user_input , arg, &exit_status );
free(user_input );
free(args);
}

return (0);
}
