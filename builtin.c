#include "shell.h"

/**
 * dispEnv - Displays environment variables.
 * @cmd: Parsed Command.
 * @er: Status of the last executed command.
 *
 * Return: Always returns 0.
 */
int dispEnv(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
	size_t i;
	int len;
	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * dispHelp - Displays help for a builtin.
 * @cmd: Parsed Command.
 * @er: Status of the last executed command.
 *
 * Return: 0 on success, -1 on failure.
 */
int dispHelp(char **cmd, __attribute__((unused)) int er)
{
	int fd, fw, rd = 1;
	char c
	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			return (-1);
		}
	}
	putchar('\n');
	return (0);
}

/**
 * execEcho - Execute echo cases.
 * @st: Status of the last executed command.
 * @cmd: Parsed Command.
 *
 * Return: Always returns 0 or executes normal echo.
 */
int execEcho(char **cmd, int st)
{
	char *path;
	unsigned int pid = getppid();
	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);
	}
	else
		return (print_echo(cmd));
	return (1);
}

/**
 * dispHistory - Display user input history in Simple Shell.
 * @c: Parsed Command.
 * @s: Status of last execution.
 *
 * Return: 0 on success, -1 on failure.
 */
int dispHistory(__attribute__((unused)) char **c, __attribute__((unused)) int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
		return (-1);
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = _itoa(counter);
		PRINTER(er);
		free(er);
		PRINTER(" ");
		PRINTER(line);
	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}

/**
 * print_echo - Execute normal Echo.
 * @cmd: Parsed Command.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_echo(char **cmd)
{
	pid_t pid;
	int status;
	pid = fork();

	if (pid == 0)
	{
		if (execve("/bin/echo", cmd, environ) == -1)
			return (-1);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}


