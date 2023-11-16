#include "shell.h"

/**
 * printEnv - Display the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on error
 */
int printEnv(FuncInfo *info) {
    if (!info) {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }
    printListStr(info->env);
    return 0;
}

/**
 * getEnvVar - Retrieve the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: Name of the environment variable
 * Return: The value of the variable, NULL if not found or on error
 */
char *getEnvVar(FuncInfo *info, const char *name) {
    if (!info) {
        fprintf(stderr, "Error: info is NULL\n");
        return NULL;
    }
    if (!name) {
        fprintf(stderr, "Error: name is NULL\n");
        return NULL;
    }
    StringList *node = info->env;
    char *p;
    while (node) {
        p = startsWith(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * setEnvVar - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int setEnvVar(FuncInfo *info) {
    if (!info) {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }
    if (info->argc != 3) {
        _ePuts("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * unsetEnvVar - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0 on success, 1 on failure
 */
int unsetEnvVar(FuncInfo *info)
{
	int i;

	if (info == NULL)
	{
		fprintf(stderr, "Error: info is NULL\n");
		return (1);
	}

	if (info->argc == 1)
	{
		_ePuts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvList - Populates the env linked list from the current environment variables.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int populateEnvList(FuncInfo *info) {
    StringList *node = NULL;
    size_t i = 0;

	if (!info) {
        fprintf(stderr, "Error: info is NULL\n");
        return 1;
    }
    for (i = 0; environ[i]; i++) {
        if (addNodeEnd(&node, environ[i], 0) == NULL) {
            free_list(&node); 
            return 1;
        }
    }
    info->env = node;
    return 0;
}
