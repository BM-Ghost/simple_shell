#include "shell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * getShellHistoryFile - gets the history file
 *  * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *getShellHistoryFile(ShellInfo *info)
{
    char *buffer, *homeDirectory;

    homeDirectory = getShellEnvironmentVariable(info, "HOME=");

    if (!homeDirectory)
        return NULL;

    buffer = malloc(sizeof(char) * (stringLength(homeDirectory) + stringLength(HISTORY_FILE) + 2));
    if (!buffer)
    {
        free(homeDirectory);  
        return NULL;
    }

    buffer[0] = 0;
    strncpy(buffer, homeDirectory, stringLength(homeDirectory));
    strcat(buffer, "/");
    strcat(buffer, HISTORY_FILE);

    free(homeDirectory);  

    return buffer;
}


/**
 * writeShellHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeShellHistory(ShellInfo *info)
{
    ssize_t fileDescriptor;
    char *fileName = getShellHistoryFile(info);
    List *node = NULL;

    if (!fileName)
        return -1;

    fileDescriptor = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(fileName);

    if (fileDescriptor == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        printToDescriptor(node->data, fileDescriptor);
        putToDescriptor('\n', fileDescriptor);
    }

    putToDescriptor(BUFFER_FLUSH, fileDescriptor);
    close(fileDescriptor);

    return 1;
}

/**
 * readShellHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readShellHistory(ShellInfo *info)
{
    int i, lastIndex = 0, lineCount = 0;
    ssize_t fileDescriptor, readLength, fileSize = 0;
    struct stat fileStat;
    char *buffer = NULL, *fileName = getShellHistoryFile(info);

    if (!fileName)
        return 0;

    fileDescriptor = open(fileName, O_RDONLY);
    free(fileName);

    if (fileDescriptor == -1)
        return 0;

    if (!fstat(fileDescriptor, &fileStat))
        fileSize = fileStat.st_size;

    if (fileSize < 2)
        return 0;

    buffer = malloc(sizeof(char) * (fileSize + 1));
    if (!buffer)
        return 0;

    readLength = read(fileDescriptor, buffer, fileSize);
    buffer[fileSize] = 0;

    if (readLength <= 0)
        return free(buffer), 0;

    close(fileDescriptor);

    for (i = 0; i < fileSize; i++)
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            buildShellHistoryList(info, buffer + lastIndex, lineCount++);
            lastIndex = i + 1;
        }

    if (lastIndex != i)
        buildShellHistoryList(info, buffer + lastIndex, lineCount++);

    free(buffer);
    info->histCount = lineCount;

    while (info->histCount-- >= MAX_HISTORY_SIZE)
        deleteNodeAtIndex(&(info->history), 0);

    renumberShellHistory(info);

    return info->histCount;
}

/**
 * buildShellHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @lineCount: the history line count, histCount
 *
 * Return: Always 0
 */
int buildShellHistoryList(ShellInfo *info, char *buf, int lineCount)
{
    List *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, lineCount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberShellHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 *
 * Return: the new histCount
 */
int renumberShellHistory(ShellInfo *info)
{
    List *node = info->history;
    int i = 0;

    while (node)
    {
        node->number = i++;
        node = node->next;
    }

    return (info->histCount = i);
}
