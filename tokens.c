#include "shell.h"
/**
* _token_util - token command
* @iinput: Input
* Return: return tokens
*/
char **_token_util(char *iinput)
{
int buf1 = 64;
int buf2 = 0;
int post = 0;

char **tokens = malloc(buf1 * sizeof(char *));
char **b_tokens;
char deli[] = " \n\t";

if (!tokens)
{
fprintf(stderr, "There's memory allocation error\n");
exit(EXIT_FAILURE);
}

while ((tokens[post] = strtok(iinput, deli)) != NULL)
{
post++;

if (post >= buf1)
{
buf2 = buf1 * 2;
b_tokens = tokens;
tokens = _realloc_mem(tokens, buf1, buf2 *sizeof(char *));
if (!tokens)
{
free(b_tokens);
free(tokens);
fprintf(stderr, "There's memory allocation error\n");
exit(EXIT_FAILURE);
}
}
iinput = NULL;
}
tokens[post] = NULL;
return (tokens);
}
