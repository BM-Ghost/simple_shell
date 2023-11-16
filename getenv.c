#include "shell.h"

/**
 * getEnv - Returns a copy of the environment string array
 * @info: Structure containing arguments and environment information
 *
 * Returns: A copy of the environment string array
 */
char **getEnv(FuncInfo *info) {
    if (!info->environ || info->changedEnv) {
        info->environ = stringListToStrings(info->env);
        log_info("Environment changed, updating environment string array");
        info->changedEnv = 0;
    }

    return info->environ;
}

/**
 * unsetEnv - Removes an environment variable
 * @info: Structure containing arguments and environment information
 * @env_var: The environment variable to remove
 *
 * Returns: 1 on deletion, 0 otherwise
 */
int unsetEnv(FuncInfo *info, char *env_var) {
    StringList *node = info->env;
    size_t index = 0;
    char *env_var_value;

    if (!node || !env_var) {
        fprintf(stderr, "Error: Invalid arguments passed to unsetEnv\n");
        return 0;
    }

    while (node) {
        env_var_value = startsWith(node->str, env_var);
        if (env_var_value && *env_var_value == '=') {
            info->changedEnv = deleteNodeAtIndex(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }
    return info->changedEnv;
}

/**
 * setEnvVar - Initializes or modifies an environment variable
 * @info: Structure containing arguments and environment information
 * @variable: The environment variable to initialize or modify
 * @value: The value to set for the environment variable
 *
 * Returns: 0 on success, 1 on failure
 */
int setEnvVar(FuncInfo *info, char *variable, char *value) {
    char *buffer = NULL;
    StringList *node;
    char *p;

    if (!variable || !value) {
        printf("Error: Variable or value is NULL\n");
        return 1;
    }

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer) {
        printf("Error: Failed to allocate memory for buffer\n");
        return 1;
    }

    strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);

    node = info->env;
    while (node) {
        p = startsWith(node->str, variable);
        if (p && *p == '=') {
            free(node->str);
            node->str = buffer;
            info->changedEnv = 1;
            return 0;
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buffer, 0);
    free(buffer);
    info->changedEnv = 1;
    return 0;
}