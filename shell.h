#ifndef _CUSTOM_SHELL_H_
#define _CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define NORMAL_COMMAND 0
#define OR_COMMAND 1
#define AND_COMMAND 2
#define CHAIN_COMMAND 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define MAX_HISTORY_SIZE 4096

extern char **environ;

typedef struct ListNode
{
    int number;
    char *data;
    struct ListNode *next;
} List;

typedef struct CommandInfo
{
    char *argument;
    char **arguments;
    char *path;
    int argumentCount;
    unsigned int lineCount;
    int errorNumber;
    int lineCountFlag;
    char *fileName;
    List *environment;
    List *history;
    List *alias;
    char **customEnvironment;
    int environmentChanged;
    int status;

    char **commandBuffer;
    int commandBufferType;
    int readDescriptor;
    int historyCount;
} ShellInfo;

#define SHELL_INFO_INITIALIZER \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
     0, 0, 0}

typedef struct BuiltinCommand
{
    char *name;
    int (*function)(ShellInfo *);
} BuiltinCommandTable;

int isShellInteractive(ShellInfo *info);
int replaceString(char **, char *);
int replaceVariables(ShellInfo *info);
int replaceAliases(ShellInfo *);
void checkCommandChainStatus(ShellInfo *info, char *buffer, size_t *currentPosition, size_t startPosition, size_t bufferLength);
int isCommandChainDelimiter(ShellInfo *info, char *buffer, size_t *currentPosition);
char **splitString(char *, char *);
char **splitStringByChar(char *, char);
char *copyString(char *dest, char *src);
int printCharacter(char c);
void printString(char *str);
char *concatenateStrings(char *dest, char *src);
char *startsWith(const char *haystack, const char *needle);
int compareStrings(char *str1, char *str2);
int getStringLength(char *str);
void forkCommand(ShellInfo *info);
void findCommand(ShellInfo *info);
int findBuiltinCommand(ShellInfo *info);
int executeShell(ShellInfo *info, char **arguments);
void *reallocMemory(void *ptr, unsigned int oldSize, unsigned int newSize);
void freeStringArray(char **strArray);
char *findCommandPath(ShellInfo *info, char *pathString, char *command);
char *duplicateCharacters(char *pathString, int startIndex, int stopIndex);
int isExecutableCommand(ShellInfo *info, char *filePath);
int freeMemory(void **ptr);
List *nodeStartsWith(List *node, char *prefix, char c);
size_t printList(const List *head);
char **listToStrings(List *head);
void freeList(List **headPointer);
int deleteNodeAtIndex(List **head, unsigned int index);
size_t printListString(const List *head);
List *addNodeEnd(List **head, const char *str, int num);
List *addNode(List **head, const char *str, int num);
int renumberShellHistory(ShellInfo *info);
int buildShellHistoryList(ShellInfo *info, char *buffer, int lineCount);
int readShellHistory(ShellInfo *info);
int writeShellHistory(ShellInfo *info);
char *getShellHistoryFile(ShellInfo *info);
void freeShellInfo(ShellInfo *info, int all);
void setShellInfo(ShellInfo *info, char **arguments);
void initializeShellInfo(ShellInfo *info);
int setEnvironmentVariable(ShellInfo *info, char *variable, char *value);
int unsetShellEnvironment(ShellInfo *info, char *environmentVariable);
char **getShellEnvironment(ShellInfo *info);
void handleSignalInterrupt(int signalNumber);
int readShellLine(ShellInfo *info, char **bufferPointer, size_t *bufferLength);
char *strncatCustom(char *dest, const char *src, size_t n);
char *strncpyCustom(char *dest, const char *src, size_t n);
void removeComments(char *buffer);
char *convertNumber(long int num, int base, int flags);
int printInteger(int input, int fileDescriptor);
void printError(ShellInfo *info, char *errorMessage);
int errorAtoi(char *string);
int printToDescriptor(char *str, int fileDescriptor);
int putToDescriptor(char character, int fileDescriptor);
int errorPutchar(char character);
void errorPuts(char *str);
int populateShellEnvironmentList(ShellInfo *info);
int unsetShellEnvironmentVariable(ShellInfo *info);
int setShellEnvironmentVariable(ShellInfo *info);
char *getShellEnvironmentVariable(ShellInfo *info, const char *name);
int printShellEnvironment(ShellInfo *info);
int printShellAliases(ShellInfo *info);
int printAlias(List *node);
int printShellHistory(ShellInfo *info);
void chainStatus(ShellInfo *info, char *bug, size_t *curPos, size_t istPos, size_t bufLen);
int printShellHelp(ShellInfo *info);
int changeShellDirectory(ShellInfo *info);
int exitCustomShell(ShellInfo *info);
int stringToInt(char *s);
int isAlphabeticCharacter(int c);
int isChainDelimiter(ShellInfo *info, char *buffer, size_t *curPos);
int isCustomDelimiter(char character, char *delimiter);
int isShellInteractive(ShellInfo *info);
char **splitStringByChar2(char *inputString, char delimiter);
char **splitStringByString(char *inputString, char *delimiterString);
int stringLength(const char *string);
int compareCustomStrings(char *, char *);
char *startWith(const char *, const char *);
char *concatenateCustomStrings(char *dest, char *src);
char *duplicateString(const char *string);
void printCustomString(char *);
void copyMemory(void *newPointer, const void *pointer, unsigned int size);
int putcharCustom(char);
char *findCharacter(char *, char);
int bfreeMemory(void **ptr);
int freeMemoryPointer(void **ptr);
char duplicateMemory(void **);
#endif

