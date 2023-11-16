#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define PRINTER(s) printf("%s", (s)) 

void signal_to_handle(int sig);
void read_file(char *filename, char **argv);
void treat_file(char *line, int counter, FILE *fp, char **argv);
void exit_bul_for_file(char **cmd, char *line, FILE *fd);

void signal_to_handle(int sig) {
    if (sig == SIGINT) {
        PRINTER("\n$ ");
    }
}

void read_file(char *filename, char **argv) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &len, fp)) != -1) {
        counter++;
        treat_file(line, counter, fp, argv);
    }

    if (line) {
        free(line);
    }
    fclose(fp);
    exit(0);
}

void treat_file(char *line, int counter, FILE *fp, char **argv) {
    char **cmd;
    int st = 0;

    cmd = parse_cmd(line); 

    if (_strncmp(cmd[0], "exit", 4) == 0) {
        exit_bul_for_file(cmd, line, fp);
    } else if (check_builtin(cmd) == 0) {
        st = handle_builtin(cmd, st); 
        free(cmd); 
    } else {
        st = execCheck(cmd, line, counter, argv); 
        free(cmd); 
    }
}

void exit_bul_for_file(char **cmd, char *line, FILE *fd) {
    int status, i = 0;
    if (cmd[1] == NULL) {
        free(line);
        free(cmd);
        fclose(fd);
        exit(errno);
    }
    while (cmd[1][i]) {
        if (!isdigit(cmd[1][i++])) {
            perror("illegal number");
            exit(EXIT_FAILURE); 
        }
    }
    status = atoi(cmd[1]);
    free(line);
    free(cmd);
    fclose(fd);
    exit(status);
}


