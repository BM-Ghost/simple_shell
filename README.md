# Simple Shell Project

This is a Unix command line interpreter developed as part of an academic project by Meshack Bwire and Claudia (Chelsea) Ageha.

## General

- **Editors:** Allowed editors include vi, vim, and emacs.
- **Compilation:** All files will be compiled on Ubuntu 20.04 LTS using gcc with specific options (-Wall -Werror -Wextra -pedantic -std=gnu89).
- **File Endings:** Ensure all your files end with a new line.
- **README.md:** A mandatory README.md file at the root of the project folder.
- **Code Style:** Use the Betty style, which will be checked using betty-style.pl and betty-doc.pl.
- **Memory Leaks:** Ensure the shell does not have any memory leaks.
- **Functions per File:** Each file should contain no more than 5 functions.
- **Header Files:** Use include guards for all header files.
- **System Calls:** Use system calls only when necessary.

## Allowed Functions and System Calls

A list of allowed functions and system calls is provided in the repository.

## Project Overview

This shell implementation serves as a basic command line interpreter. Its functionalities evolve progressively across versions:

### Simple Shell 0.1

- Handles command lines with arguments.

### Simple Shell 0.2

- Handles the PATH.
- Ensures fork is not called if the command doesn’t exist.

### Simple Shell 0.3

- Implements the exit built-in, allowing shell exit using the 'exit' command.
- Usage: exit

### Simple Shell 0.4

- Implements the env built-in, which prints the current environment.

### Simple Shell 1.0

- Implements setenv and unsetenv built-in commands:
  - `setenv VARIABLE VALUE`: Initializes or modifies an environment variable.
  - `unsetenv VARIABLE`: Removes an environment variable.
- Implements the cd built-in command:
  - `cd [DIRECTORY]`: Changes the current directory of the process.
  - Handles the command `cd -` and updates the PWD environment variable accordingly.
- Handles command separator `;`.

## Project Development

- **Version Progression:** The shell evolves across different versions, implementing additional functionalities.
- **Development Goals:** Enhance the shell capabilities as per the defined version objectives.

## GitHub Repositories

- Meshack Bwire's GitHub: [BM-Ghost](https://github.com/BM-Ghost)
- Claudia (Chelsea) Ageha's GitHub: [Claudia-O-A](https://github.com/Claudia-O-A)
- Repo: [BM-Ghost](https://github.com/BM-Ghost/simple_shell)

---

