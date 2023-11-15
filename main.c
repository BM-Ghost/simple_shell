#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int argc, char **argv)
{
    ShellInfo shellInfo = SHELL_INFO_INITIALIZER;
    int fileDescriptor = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fileDescriptor)
        : "r" (fileDescriptor));

    if (argc == 2)
    {
        fileDescriptor = open(argv[1], O_RDONLY);
        if (fileDescriptor == -1)
        {
            if (errno == EACCES)
            {
                fprintf(stderr, "Error: Permission denied to open %s\n", argv[1]);
                exit(98);
            }
            if (errno == ENOENT)
            {
                fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
                exit(98);
            }
            fprintf(stderr, "Error: Failed to open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        shellInfo.readDescriptor = fileDescriptor;
    }

    populateShellEnvironmentList(&shellInfo);
    readShellHistory(&shellInfo);
    executeShell(&shellInfo, argv);

    return EXIT_SUCCESS;
}

