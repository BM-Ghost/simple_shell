#include "shell.h"

/**
* manage_signal - handle CTRL + C
* @sigint: Signal
* Return: Void character
*/
void manage_signal(int sigint)
{
if (sigint == SIGINT)
write(2, "\n#shell_CL$ ", 11);
}
