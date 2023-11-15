#include "shell.h"

/**
 * runShell - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int executeShell(ShellInfo *info, char **av)
{
    ssize_t readStatus = 0;
    int builtinRet = 0;

    while (readStatus != -1 && builtinRet != -2)
    {
        initializeShellInfo(info);

        if (isShellInteractive(info))
            printString("$ ");

        errorPutchar(BUFFER_FLUSH);

        readStatus = getInput(info);

        if (readStatus != -1)
        {
            setShellInfo(info, av);
            builtinRet = findBuiltinCommand(info);

            if (builtinRet == -1)
                findCommand(info);
        }
        else if (isShellInteractive(info))
            errorPutchar('\n');

        freeShellInfo(info, 0);
    }

    writeShellHistory(info);
    freeShellInfo(info, 1);

    if (!isShellInteractive(info) && info->status)
        exit(info->status);

    if (builtinRet == -2)
    {
        if (info->errNum == -1)
            exit(info->status);
        exit(info->errNum);
    }

    return builtinRet;
}

/**
 * findBuiltinCommand - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int findBuiltinCommand(ShellInfo *info)
{
    int i, builtinRet = -1;
    BuiltinCommandTable shellBuiltinTbl[] = {
        {"exit", exitShell},
        {"env", printShellEnvironment},
        {"help", printShellHelp},
        {"history", printShellHistory},
        {"setenv", setShellEnvironmentVariable},
        {"unsetenv", unsetShellEnvironmentVariable},
        {"cd", changeDir},
        {"alias", printShellAliases},
        {NULL, NULL}};

    for (i = 0; shellBuiltinTbl[i].name; i++)
        if (compareStrings(info->argv[0], shellBuiltinTbl[i].name) == 0)
        {
            info->lineCount++;
            builtinRet = shellBuiltinTbl[i].function(info);
            break;
        }

    return builtinRet;
}

/**
 * findShellCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(ShellInfo *info)
{
    char *path = NULL;
    int i, numArgs = 0;

    info->path = info->argv[0];

    if (info->lineCountFlag == 1)
    {
        info->lineCount++;
        info->lineCountFlag = 0;
    }

    for (i = 0; info->arg[i]; i++)
        if (!isShellDelimiter(info->arg[i], " \t\n"))
            numArgs++;

    if (!numArgs)
        return;

    path = findCommandPath(info, getShellEnvironmentVariable(info, "PATH="), info->argv[0]);

    if (path)
    {
        info->path = path;
        forkCommand(info);
    }
    else
    {
        if ((isShellInteractive(info) || getShellEnvironmentVariable(info, "PATH=") || info->argv[0][0] == '/') && findCommand(info, info->argv[0])) 
            forkCommand(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 150;
            printError(info, "No Command\n");
        }
    }
}


/**
 * forkCommand - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(ShellInfo *info)
{
    pid_t childPid;

    childPid = fork();

    if (childPid == -1)
    {
        printError(info, "Fatal Error:");
        return;
    }

    if (childPid == 0)
    {
        if (execve(info->path, info->argv, getShellEnvironment(info)) == -1)
        {
            freeShellInfo(info, 1);

            if (errno == EACCES)
                exit(98);

            exit(1);
        }
    }
    else
    {
        wait(&(info->status));

        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);

            if (info->status == 150)
                printError(info, "Permission denied\n");
        }
    }
}
