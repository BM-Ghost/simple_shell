#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    while (1) {
        if (isatty(STDIN_FILENO)) {
            printf("($)");
            fflush(stdout);
        }

        if (getline(&buffer, &bufsize, stdin) == -1) {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            exit(EXIT_SUCCESS);
        

        free(buffer);
    }

    return 0;
}

