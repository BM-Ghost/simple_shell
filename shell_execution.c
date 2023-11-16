#include "shell.h"
/**
* hshFunc - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hshFunc(FuncInfo *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_ret = 0;

	while (read_status != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			customPuts("$ ");
		_eputChar(BUFFER_FLUSH);
		read_status = getInput(info);
		if (read_status != -1)
		{
			setInfo(info, av);
			builtin_ret = findBuiltIn(info);
			if (builtin_ret == -1)
				findCommand(info);
		}
		else if (interactive(info))
			putchar('\n');
		freeInfo(info, 0);
	}
	writeHistory(info);
	freeInfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_code == -1)
			exit(info->status);
		exit(info->err_code);
	}
	return (builtin_ret);
}
/**
* findBuiltIn - finds a BuiltInCmd command
* @info: the parameter & return info struct
*
* Return: -1 if BuiltInCmd not found,
* 0 if BuiltInCmd executed successfully,
* 1 if BuiltInCmd found but not successful,
* -2 if BuiltInCmd signals exit()
*/
int findBuiltIn(FuncInfo *info)
{
	int i, builtin_ret = -1;
	BuiltInCommand builtintbl[] = {
		{"exit", exitShell},
		{"env", printEnv},
		{"help", printHelp},
		{"history", printHistory},
		{"setenv", setEnvVar},
		{"unsetenv", unsetEnvVar},
		{"cd", changeDir},
		{"alias", printAliases},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].cmd_type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].cmd_type) == 0)
		{
			info->line_cnt++;
			builtin_ret = builtintbl[i].command_func(info);
			break;
		}
	return (builtin_ret);
}
/**
* findCommand - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void findCommand(FuncInfo *info)
{
	char *path = NULL;
	int i, num_args = 0;

	info->path = info->argv[0];

	if (info->line_cnt_flag == 1)
	{
		info->line_cnt++;
		info->line_cnt_flag = 0;
	}
	for (i = 0; info->args[i]; i++)
		if (!isDelimiter(info->args[i], " \t\n"))
			num_args++;
	if (!num_args)
		return;
	path = findPath(info, getEnvVar(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((isInteractive(info) || getEnvVar(info, "PATH=")
			|| info->argv[0][0] == '/') && findCommand(info, info->argv[0]))
		forkCommand(info);
		else if (*(info->args) != '\n')
		{
			info->status = 150;
			printErr(info, "No Command\n");
		}
	}
}
/**
* forkCommand - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void forkCommand(FuncInfo *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
	/* TODO: PUT ERROR FUNCTION */
		perror("Fatal Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnv(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(98);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 150)
				printErr(info, "Permission denied\n");
		}
	}
}
