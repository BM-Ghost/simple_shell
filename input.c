#include "shell.h"

/**
 * input_verify - Validates and finds executable in PATH
 * @agu: Command arguments
 * @arg: Program name
 * Return: Path to executable or NULL on failure
 */

char *input_verify(char **agu, char **arg)
{
char *n_agu, *start, *s_agu = "/", **t_path, hold_en[1024];
int i = 0;
if (agu[0][0] == '/' || agu[0][0] == '.')
{
n_agu = agu[0];
if ((access(n_agu, F_OK) == -1))
{
fprintf(stderr, "%s: No such file or directory\n", arg[0]);
return ("Fail to acess");
}
}
else
{
strcpy(hold_en, getenv("PATH"));
t_path = _token_util(hold_en);
while (t_path[i])
{
start = string_append(s_agu, agu[0]);
n_agu = string_append(t_path[i], start);
if ((access(n_agu, F_OK) == -1))
{
free(n_agu);
free(start);
}
else
{
free(t_path);
free(start);
return (n_agu);
}
i++;
}
free(t_path);
fprintf(stderr, "%s: No such file or directory\n", arg[0]);
return ("Fail to acess");
}
return (n_agu);
}
