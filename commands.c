#include "shell.h"

/**
 * exe_cmd - Executes the commands
 * @agu: Command string and arguments
 * @arg: Array of strings containing command arguments
 * @exiti: Pointer to the exit status
 * Return: 1 on success, otherwise returns 1
 */

int exe_cmd(char **agu, char **arg, int *exiti)
{
pid_t pid;
char *n_agu;
int tty_status ;

n_agu = input_verify(agu, arg);
if (strcmp(n_agu, "Fail access") == 0)
return (1);

pid = fork();
if (pid == 0)
{
if (execve(n_agu, arg, environ) == -1)
{
perror("Error ");
exit(EXIT_FAILURE);
}
}

else if (pid < 0)
{
perror("Error ");
free(n_agu);
return (1);
}

else
{
waitpid(-1, &tty_status , 0);
if (WEXITSTATUS(tty_status ))
*exiti = WEXITSTATUS(tty_status );
if (agu[0][0] != '/' && agu[0][0] != '.')
free(n_agu);
return (1);
}

return (1);
}
