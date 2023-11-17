#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>

/**
* struct choice_built - getting the commands in validation
* @naming_built: naming
* @fun_built: Pointer
*/

typedef struct choice_built
{
char *naming_built;
int (*fun_built)(char **, char *, int *);
} choice_t;

void manage_signal(int sigint);
char *fetch_env(char *envronment_variable);
char *input_verify(char **agu, char **arg);
char **_token_util(char *iinput);
void *_realloc_mem(void *p, unsigned int p_s, unsigned int n_s);
int unset_env(char **av, char *input, int *exiti);
int set_env(char **av, char *input, int *exiti);
int print_env(char **av, char *input, int *exiti);
int curr_dir(char **av, char *input, int *exiti);
int _exe_builtin(char **a, char *user_input , char **args, int *exit_status );
int exit(char **av, char *input, int *exiti);
int exe_cmd(char **agu, char **arg, int *exiti);
int space_ver(char *iinput);
char *string_append(char *str_one, char *str_two);

extern char **environ;

#endif
