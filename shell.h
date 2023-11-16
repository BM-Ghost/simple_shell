#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH '\0'

/* for command chaining */
#define NORM	0
#define SH_OR		1
#define SH_AND		2
#define SH_CHAIN	3

/* for convertNum() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define _GETLINE 0
#define STRTOK_ON 0

#define HISTORY_FILE	".simple_shell_history"
#define MAX_HISTORY	4096

extern char **env;

/**
 * struct StringNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct StringNode
{
	int num;
	char *str;
	struct StringNode *next;
} StringList;

/**
 *struct FuncArgs - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@args: a string generated from getline containing arguements
 *@argv: an array of strings generated from args
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_cnt: the error count
 *@err_code: the error code for exit()s
 *@line_cnt_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@changedEnv: on if environ was changed
 *@status: the return status of the last exec'd command
 *@chainBuf: address of pointer to chainBuf, on if chaining
 *@chainBufType: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@historycount: the history line number count
 */

typedef struct FuncArgs
{
	char *args;
	char **argv;
	char *path;
	int argc;
	unsigned int line_cnt;
	int err_code;
	int line_cnt_flag;
	char *fname;
	StringList *mode_env;
	StringList *history;
	StringList *alias;
	char **env;
	int changedEnv;
	int status;
	char **chainBuf; /* pointer to cmd ; chain buffer, for memory mangement */
	int chainBufType; /* CMD_type ||, &&, ; */
	int readfd;
	int historycount;
} FuncInfo;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct BuiltInCmd - contains a BuiltInCmd string and related function
 *@cmd_type: the BuiltInCmd command flag
 *@command_func: the function
 */
typedef struct BuiltInCmd
{
	char *cmd_type;
	int (*command_func)(FuncInfo *);
} BuiltInCommand;

int isInteractive(FuncInfo *info);
int replaceStr(char **, char *);
int replaceVariables(FuncInfo *info);
int replaceAlias(FuncInfo *);
void checkChainStatus(FuncInfo *info, char *buf, size_t *current_position, size_t start_position, size_t buffer_length);
int isChainDelimiter(FuncInfo *info, char *buf, size_t *current_position);
char **strtow(char *, char *);
char **_strtow(char *, char);
char *strcpy(char *dest, char *src);
int putchar(char c);
void putstr(char *str);
char *cntstr(char *dest, char *src);
char *startsWith(const char *haystack, const char *needle);
int compStr(char *str1, char *str2);
int getStrLn(char *str);
void forkCommand(FuncInfo *info);
void findCommand(FuncInfo *info);
int findBuiltIn(FuncInfo *info);
int hshFunc(FuncInfo *info, char **av);
void *resizeMem(void *ptr, unsigned int old_size, unsigned int new_size);
void freeStringArray(char **str_arr);
char *findPath(FuncInfo *info, char *path_str, char *cmd);
char *copyChars(char *path_str, int start_index, int stop_index);
int isExecutable(FuncInfo *info, char *file_path);
int freePtr(void **ptr);
ssize_t getNodeIndex(StringList *head, StringList *node);
StringList *nodeStartsWith(StringList *node, char *prefix, char c);
size_t printList(const StringList *head);
char **stringListToStrings(StringList *head);
void freeList(StringList **head_ptr);
int deleteNodeAtIndex(StringList **head, unsigned int index);
size_t printListStr(const StringList *head);
StringList *addNodeEnd(StringList **head, const char *str, int num);
StringList *addNode(StringList **head, const char *str, int num);
int renumberHistory(FuncInfo *info);
int buildHistory(FuncInfo *info, char *buf, int line_cnt);
int readHistory(FuncInfo *info);
int writeHistory(FuncInfo *info);
char *getHistoryFile(FuncInfo *info);
void freeInfo(FuncInfo *info, int all);
void setInfo(FuncInfo *info, char **av);
void initializeInfo(FuncInfo *info);
int setEnvVar(FuncInfo *info, char *variable, char *value);
int unsetEnv(FuncInfo *info, char *env_var);
char **getEnv(FuncInfo *info);
void handleSigint(int signal_number);
int getLine(FuncInfo *info, char **buffer_ptr, size_t *buffer_length);
ssize_t readBuf(FuncInfo *info, char *buffer, size_t *buffer_size);
ssize_t getInput(FuncInfo *info);
ssize_t inputBuf(FuncInfo *info, char **buffer, size_t *buffer_length);
char *strncat(char *dest, const char *src, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
void removeComments(char *buf);
char *convertNum(long int num, int base, int flags);
int printD(int input, int fd);
void printErr(FuncInfo *info, char *estr);
int _errAtoi(char *s);
int _putsFd(char *str, int fd);
int _putFd(char c, int fd);
int _eputChar(char c);
void _ePuts(char *str);
int populateEnvList(FuncInfo *info);
int unsetEnvVar(FuncInfo *info);
int setEnvVar(FuncInfo *info);
char *getEnvVar(FuncInfo *info, const char *name);
int printEnv(FuncInfo *info);
int printAliases(FuncInfo *info);
int printAlias(StringList *node);
int setAlias(FuncInfo *info, char *alias_str);
int unsetAlias(FuncInfo *info, char *alias_str);
int printHistory(FuncInfo *info);
void chainStat(FuncInfo *info, char *bug, size_t *cur_pos, size_t ist_pos, size_t buf_len);
int printHelp(FuncInfo *info);
int changeDir(FuncInfo *info);
int exitShell(FuncInfo *info);
int strToInt(char *s);
int isAlphabetic(int c);
int isChainDel(FuncInfo *info, char *buf, size_t *cur_pos);
int isDelimiter(char c, char *delim);
int isInteractive(FuncInfo *info);
char **_strtow(char *input_str, char del);
char **strtow(char *input_str, char *del_s);
int strLen(const char *string);
int _strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *strConcat(char *dest, char *src);
char *strDuplicate(const char *string);
void customPuts(char *);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
int putchar(char);
char *_strchr(char *, char);
int bfree(void **ptr);
int freePtr(void **ptr);
char strDup(void **);
#endif
