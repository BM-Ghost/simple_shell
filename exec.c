#include "shell.h"

/**
 * handle_builtin - Handles execution of built-in commands
 * @cmd: Parsed command
 * @er: Status of the last execution
 * Return: -1 on failure, 0 on success (Execute Built-in Command)
 */
int handle_builtin(char **cmd, int er) {
    BuiltInCmd bil[] = {
        {"cd", changeDir},
        {"env", dispEnv},
        {"help", dispHelp},
        {"echo", execEcho},
        {"history", dispHistory},
        {NULL, NULL}
    };
    int i = 0;

    while (bil[i].command != NULL) {
        if (strcmp(cmd[0], bil[i].command) == 0) {
            return bil[i].fun(cmd, er);
        }
        i++;
    }
    return -1; 
}

/**
 * execCheck - Executes a simple shell command (Fork, Wait, Execute)
 * @cmd: Parsed command
 * @input: User input
 * @c: Shell execution time case of command not found
 * @argv: Program name
 * Return: 1 if command is NULL, -1 for wrong command, 0 if command executed
 */
int execCheck(char **cmd, char *input, int c, char **argv) {
    int status;
    pid_t pid;

    if (cmd[0] == NULL) {
        return -1;
    }
    pid = fork();
    if (pid == -1) {
        perror("Fork error");
        return -1;
    }
    if (pid == 0) {
        if (strncmp(cmd[0], "./", 2) != 0 && strncmp(cmd[0], "/", 1) != 0) {
            searchExecPath(cmd);
        }

        if (execvp(cmd[0], cmd) == -1) {
            printErr(cmd[0], c, argv);
            free(input);
            free(cmd);
            exit(EXIT_FAILURE);
        }
        return EXIT_SUCCESS;
    }

    wait(&status);
    return 0;
}

/**
 * signal_handler - Handles the SIGINT signal (^C)
 * @sig: Captured signal
 * Return: Void
 */
void signal_handler(int sig) {
    if (sig == SIGINT) {
        PRINTER("\n$ "); 
    }
}
