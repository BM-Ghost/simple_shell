#include "shell.h"

/**
 * printShellEnvironment - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int printShellEnvironment(ShellInfo *info)
{
    if (info == NULL)
    {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }
    printListString(info->environment);
    return 0;
}

/**
 * getShellEnvironmentVariable - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name
 *
 * Return: the value
 */
char *getShellEnvironmentVariable(ShellInfo *info, const char *name)
{
    List *node = info->environment;
    char *p;

    if (info == NULL)
    {
        fprintf(stderr, "Error: info is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        fprintf(stderr, "Error: name is NULL\n");
        return NULL;
    }

    while (node)
    {
        p = startWith(node->data, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * setShellEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure
 */
int setShellEnvironmentVariable(ShellInfo *info)
{
    if (info == NULL)
    {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }

    if (info->argc != 3)
    {
        errorPuts("Incorrect number of arguments\n");
        return 1;
    }

    if (setenv(ShellInfo->arg[1], ShellInfo->arg[2], 1) != 0)
        return 0;

    return 1;
}


/**
 * unsetShellEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure
 */
int unsetShellEnvironmentVariable(ShellInfo *info)
{
    int i;

    if (info == NULL)
    {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }

    if (info->argc == 1)
    {
        errorPuts("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
    {
        if (unsetenv(info->argv[i]) != 0)
        {
            perror("unsetenv");
            return 1;
        }
    }

    return 0;
}


/**
 * populateShellEnvironmentList - populates environment linked list
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure
 */
int populateShellEnvironmentList(ShellInfo *info)
{
    List *node = NULL;
    size_t i;

    if (info == NULL)
    {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    info->environment = node;
    return 0;
}

