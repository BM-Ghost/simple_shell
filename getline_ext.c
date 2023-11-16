#include "shell.h"

/**
 * inputBuf - Reads and buffers chained commands from standard input
 * @info: Parameter struct containing shell information
 * @buffer: Address of the buffer to store the input
 * @buffer_length: Address of the variable storing buffer length
 *
 * Return: Number of bytes read
 */
ssize_t inputBuf(FuncInfo *info, char **buffer, size_t *buffer_length) {
    ssize_t read_bytes = 0;
    size_t length_param = 0;

    if (!*buffer_length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);

        #if _GETLINE
            read_bytes = getline(buffer, &length_param, stdin);
        #else
            read_bytes = _getline(info, buffer, &length_param);
        #endif

        if (read_bytes > 0) {
            if ((*buffer)[read_bytes - 1] == '\n') {
                (*buffer)[read_bytes - 1] = '\0';
                read_bytes--;
            }
            info->line_cnt_flag = 1;
            removeComments(*buffer);
            buildHistory(info, *buffer, info->historycount++);
            *buffer_length = read_bytes;
            info->chainBuf = buffer;
        }
    }
    return read_bytes;
}

/**
 * getInput - Retrieves a line of input without the newline character
 * @info: Parameter struct containing shell information
 *
 * Return: Number of bytes read
 */
ssize_t getInput(FuncInfo *info) {
    static char *buf;
    static size_t buf_index, iterator, buf_length;
    ssize_t read_bytes = 0;
    char **buffer_pointer = &(info->args), *pointer;

    putchar(BUFFER_FLUSH);
    read_bytes = inputBuf(info, &buf, &buf_length);
    if (read_bytes == -1)
        return -1;

    if (buf_length) {
        iterator = buf_index;
        pointer = buf + buf_index;
        check_chain(info, buf, &iterator, buf_index, buf_length);

        while (iterator < buf_length) {
            if (isChainDel(info, buf, &iterator))
                break;
            iterator++;
        }

        buf_index = iterator + 1;

        if (buf_index >= buf_length) {
            buf_index = buf_length = 0;
            info->chainBufType = NORM;
        }

        *buffer_pointer = pointer;
        return _strlen(pointer);
    }

    *buffer_pointer = buf;
    return read_bytes;
}

/**
 * readBuf - Reads a buffer from a file descriptor
 * @info: Parameter struct containing shell information
 * @buffer: Buffer to read into
 * @buffer_size: Address of buffer size
 *
 * Return: Status of the read operation
 */
ssize_t readBuf(FuncInfo *info, char *buffer, size_t *buffer_size) {
    ssize_t read_status = 0;

    if (*buffer_size)
        return 0;

    read_status = read(info->readfd, buffer, READ_BUFFER_SIZE);
    if (read_status >= 0)
        *buffer_size = read_status;

    return read_status;
}

/**
 * getLine - Reads the next line of input from STDIN
 * @info: Parameter struct containing shell information
 * @buffer_ptr: Address of pointer to buffer, preallocated or NULL
 * @buffer_length: Size of preallocated buffer_ptr buffer if not NULL
 *
 * Return: Length of the buffer
 */
int getLine(FuncInfo *info, char **buffer_ptr, size_t *buffer_length) {
    static char buf[READ_BUFFER_SIZE];
    static size_t i = 0, len = 0;
    size_t k = 0;
    ssize_t r = 0, str = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *buffer_ptr;
    if (p && buffer_length)
        str = *buffer_length;

    if (i == len)
        i = len = 0;

    r = readBuf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = _realloc(p, str, str ? str + k : k + 1);
    if (!new_p) /* Memory allocation failure */
        return (p ? free(p), -1 : -1);

    if (str)
        strncat(new_p, buf + i, k - i);
    else
        strncpy(new_p, buf + i, k - i + 1);

    str += k - i;
    i = k;
    p = new_p;

    if (buffer_length)
        *buffer_length = str;

    *buffer_ptr = p;
    return str;
}

/**
 * sigintHandler - Handles SIGINT signal (Ctrl+C)
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num) {
    customPuts("\n$ ");
    putchar(BUFFER_FLUSH);
}
