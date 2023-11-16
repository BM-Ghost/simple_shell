#include "shell.h"

/**
 * initializeInfo - Initializes all fields in a FuncInfo struct to default values
 * @info: Pointer to FuncInfo struct
 */
void initializeInfo(FuncInfo *info) {
    info->args = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * setInfo - Initializes FuncInfo struct fields using given argument vector
 * @info: Pointer to FuncInfo struct
 * @av: Argument vector
 */
void setInfo(FuncInfo *info, char **av) {
    int i = 0;

    info->fname = av[0];
    if (info->args) {
        info->argv = strtow(info->args, " \t");
        if (!info->argv) {
            fprintf(stderr, "Error: Failed to allocate memory for argv\n");
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv) {
                info->argv[0] = strDup(info->args);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++);
        info->argc = i;

        replaceAlias(info);
    }
}

/**
 * freeInfo - Frees allocated memory in FuncInfo struct fields
 * @info: Pointer to FuncInfo struct
 * @all: Boolean flag, True if freeing all fields, False otherwise
 */
void freeInfo(FuncInfo *info, int all) {
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (all) {
        if (!info->chainBuf)
            free(info->args);
        if (info->env)
            freeList(&(info->env));
        if (info->history)
            freeList(&(info->history));
        if (info->alias)
            freeList(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->chainBuf);
        if (info->readfd > 2)
            close(info->readfd);
        putchar(BUFFER_FLUSH);
    }
}
