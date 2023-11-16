#include "shell.h"

/**
 * searchExecPath - Search for an executable command in the $PATH environment variable
 * @cmd: Parsed input command
 *
 * This function searches for the executable command within the directories specified in the $PATH.
 * Returns: 0 on success (executable found and updated in cmd), 1 on failure (executable not found).
 */
int searchExecPath(char **cmd) {
    char *path, *value, *cmd_path;
    struct stat buf;

    path = _getenv("PATH");
    value = _strtok(path, ":");
    while (value != NULL) {
        cmd_path = build(*cmd, value);
        if (stat(cmd_path, &buf) == 0) {
            *cmd = strDup(cmd_path); 
            free(cmd_path);
            free(path);
            return 0;
        }
        free(cmd_path);
        value = _strtok(NULL, ":");
    }
    free(path);

    return 1; 
}

/**
 * build - Build the full path of a command
 * @token: Executable command
 * @value: Directory containing the command
 *
 * Returns: Parsed full path of the command or NULL if failed to allocate memory.
 */
char *build(char *token, char *value) {
    char *cmd;
    size_t len;

    len = _strlen(value) + _strlen(token) + 2;
    cmd = malloc(sizeof(char) * len);
    if (cmd == NULL) {
        return NULL; 
    }

    memset(cmd, 0, len);
    cmd = _strcat(cmd, value);
    cmd = _strcat(cmd, "/");
    cmd = _strcat(cmd, token);

    return cmd;
}

/**
 * _getenv - Get the value of an environment variable by name
 * @name: Environment variable name
 *
 * Returns: The value of the environment variable or NULL if not found or failed to allocate memory.
 */
char *_getenv(char *name) {
    size_t nl, vl;
    char *value;
    int i, x, j;

    nl = _strlen(name);
    for (i = 0 ; environ[i]; i++) {
        if (_strncmp(name, environ[i], nl) == 0) {
            vl = _strlen(environ[i]) - nl;
            value = malloc(sizeof(char) * (vl + 1));
            if (!value) {
                perror("Unable to allocate memory");
                return NULL; 
            }

            j = 0;
            for (x = nl + 1; environ[i][x]; x++, j++) {
                value[j] = environ[i][x];
            }
            value[j] = '\0';

            return value;
        }
    }

    return NULL; 
}
