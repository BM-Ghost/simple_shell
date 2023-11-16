#include "shell.h"
/**
 * check_builtin - check BuiltInCmd
 *
 * @cmd:command to check
 * Return: 0 Succes -1 Fail
 */
int check_builtin(char **cmd)
{
	BuiltInCmd fun[] = {
		{"cd", NULL},
		{"help", NULL},
		{"echo", NULL},
		{"history", NULL},
		{NULL, NULL}};
	int i = 0;

	if (*cmd == NULL)
	{
		return (-1);
	}

	while ((fun + i)->command)
	{
		if (_strcmp(cmd[0], (fun + i)->command) == 0)
			return (0);
		i++;
	}
	return (-1);
}
/**
 * creat_envi - Creat Array of Enviroment Variable
 * @envi: Array of Enviroment Variable
 * Return: Void
 */
void creat_envi(char **envi)
{
	int i;

	for (i = 0; environ[i]; i++)
		envi[i] = strDup(environ[i]);
	envi[i] = NULL;
}

