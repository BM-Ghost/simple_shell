#include "shell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * getHistoryFile - Retrieves the path of the history file
 * @info: Parameter struct containing shell information
 *
 * Return: Allocated string containing the history file path
 */
char *getHistoryFile(FuncInfo *info) {
    char *buf, *home_dir;

    home_dir = getEnvVar(info, "HOME=");
    if (!home_dir)
        return NULL;
    buf = malloc(sizeof(char) * (strLen(home_dir) + strLen(HISTORY_FILE) + 2));
    if (!buf)
        return NULL;
    buf[0] = 0;
    strncpy(buf, home_dir);
    _strcat(buf, "/");
    _strcat(buf, HISTORY_FILE);

    return buf;
}

/**
 * writeHistory - Writes the shell history to a file
 * @info: Parameter struct containing shell information
 *
 * Return: 1 on success, -1 on failure
 */
int writeHistory(FuncInfo *info) {
    ssize_t file_descriptor;
    char *file_name = getHistoryFile(info);
    StringList *node = NULL;

    if (!file_name)
        return -1;

    file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);

    if (file_descriptor == -1)
        return -1;
    for (node = info->history; node; node = node->next) {
        _putsFd(node->str, file_descriptor);
        _putFd('\n', file_descriptor);
    }
    _putFd(BUFFER_FLUSH, file_descriptor);
    close(file_descriptor);

    return 1;
}

/**
 * readHistory - Reads shell history from a file
 * @info: Parameter struct containing shell information
 *
 * Return: Number of lines read from history file on success, 0 on failure
 */
int readHistory(FuncInfo *info) {
    int i, last_index = 0, line_cnt = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stat;
    char *buffer = NULL, *file_name = getHistoryFile(info);

    if (!file_name)
        return 0;

    file_descriptor = open(file_name, O_RDONLY);
    free(file_name);

    if (file_descriptor == -1)
        return 0;

    if (!fstat(file_descriptor, &file_stat))
        file_size = file_stat.st_size;

    if (file_size < 2)
        return 0;

    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buffer)
        return 0;

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = 0;

    if (read_length <= 0)
        return free(buffer), 0;

    close(file_descriptor);

    for (i = 0; i < file_size; i++)
        if (buffer[i] == '\n') {
            buffer[i] = 0;
            buildHistory(info, buffer + last_index, line_cnt++);
            last_index = i + 1;
        }

    if (last_index != i)
        buildHistory(info, buffer + last_index, line_cnt++);

    free(buffer);
    info->historycount = line_cnt;

    while (info->historycount-- >= MAX_HISTORY)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);

    return info->historycount;
}

/**
 * buildHistory - Adds an entry to the shell's history linked list
 * @info: Structure containing shell information and history
 * @buf: Buffer containing the command to be added to history
 * @line_cnt: Current history line count
 *
 * Return: Always returns 0
 */
int buildHistory(FuncInfo *info, char *buf, int line_cnt) {
    StringList *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, line_cnt);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberHistory - Updates the sequence numbers of the history entries
 * @info: Structure containing shell information and history
 *
 * Return: The updated history count
 */
int renumberHistory(FuncInfo *info) {
    StringList *node = info->history;
    int i = 0;

    while (node) {
        node->num = i++;
        node = node->next;
    }

    return (info->historycount = i);
}


