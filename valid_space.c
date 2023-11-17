#include "shell.h"

/**
* space_ver - validation of the space
* @iinput: input
* Return: 1 on spaces
*/
int space_ver(char *iinput)
{
int i = 0;
int j = 1;
int space_count = 0;

space_count = strlen(iinput);

while (iinput[i] == ' ' || iinput[i] == '\n' || iinput[i] == '\t')
i++;

if (i != space_count)
j = 0;

return (j);
}
