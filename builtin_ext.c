#include "shell.h"

/**
 * printHistory - Displays the history list, one command per line, preceded
 *                by line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain a constant
 *        function prototype.
 *
 * Return: Always returns 0.
 */
int printHistory(FuncInfo *info)
{
    printList(info->history);
    return (0);
}

/**
 * unsetAlias - Removes an alias from the list of aliases
 * @info: Parameter struct
 * @alias_str: The alias string to unset
 *
 * Return: Returns 0 on success, 1 on error
 */
int unsetAlias(FuncInfo *info, char *alias_str)
{
    char *equal_sign;
    int ret;
    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign)
    {
        fprintf(stderr, "Error: Invalid alias format\n");
        return 1;
    }
    *equal_sign = '\0';
    ret = deleteNodeAtIndex(&(info->alias),
                            getNodeIndex(info->alias, nodeStartsWith(info->alias, alias_str, -1)));
    *equal_sign = '=';
    if (ret == -1)
    {
        fprintf(stderr, "Error: Alias not found\n");
        return 1;
    }
    return 0; 
}

/**
 * setAlias - sets an alias string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setAlias(FuncInfo *info, char *alias_str)
{
    char *equal_sign;
    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign) {
        fprintf(stderr, "Error: Invalid alias format\n");
        return 1;
    }
    if (!*++equal_sign) {
        return unsetAlias(info, alias_str);
    }
    unsetAlias(info, alias_str);
    if (addNodeEnd(&(info->alias), alias_str, 0) != NULL) {
        fprintf(stderr, "Error: Failed to set alias\n");
        return 1;
    }
    return 0;
}

/**
 * printAlias - Prints an alias string.
 * @node: Pointer to the alias node containing the string to be printed.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int printAlias(StringList *node)
{
    char *equal_sign = NULL, *alias_name = NULL;
    if (node)
    {
        equal_sign = _strchr(node->str, '=');
        for (alias_name = node->str; alias_name <= equal_sign; alias_name++)
            putchar(*alias_name);
        putchar('\'');
        customPuts(equal_sign + 1);
        customPuts("'\n");
        return (0);
    }
    return (1);
}

/**
 * printAliases - Prints alias strings or sets new aliases based on input.
 * @info: Pointer to the function information structure.
 *
 * Return: Always returns 0.
 */
int printAliases(FuncInfo *info)
{
    int i = 0;
    char *equal_sign = NULL;
    StringList *node = NULL;
    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        equal_sign = _strchr(info->argv[i], '=');
        if (equal_sign)
            setAlias(info, info->argv[i]);
        else
            printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
    }
    return (0);
}
