#include "shell.h"

/**
 * exit_bul - Exit the shell with a specified status.
 * @cmd: Parsed Command.
 * @input: User Input.
 * @argv: Program Name.
 * @c: Execute Count.
 *
 * Return: Void (Exits with a specific status).
 */
void exit_bul(char **cmd, char *input, char **argv, int c)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}

	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}
		else
		{
			statue = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(statue);
		}
	}
}

/**
 * changeDir - Change directory.
 * @cmd: Parsed Command.
 * @er: Status of the last executed command.
 *
 * Return: 0 on success, 1 on failure (For Old Pwd Always 0 Case No Old PWD).
 */
int changeDir(char **cmd, __attribute__((unused)) int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hshFunc");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}

	return (0);
}


