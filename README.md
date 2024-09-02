# My Shell

a custom Unix-like shell implemented in C that provides a number of built-in commands, supports external commands execution and variables assigning and exporting.

## Features

- **Execute External Commands:** Run standard Unix commands directly from the shell.
- **Variable Assignment:** Assign and store variables using `VAR=value`.
- **Export Variables:** Use the `export` command to make variables available as environment variables.
- **Built-in Commands:**
  - `mycp`: Copy files (similar to `cp`).
  - `mypwd`: Print the current working directory (similar to `pwd`).
  - `mymv`: Move or rename files (similar to `mv`).
  - `myecho`: Display a line of text or the value of a variable (similar to `echo`).

## Installation

Clone the repository and compile the shell:

```bash
git clone https://github.com/your-username/my-custom-shell.git
gcc -o myshell program.c external_command.c shell_variables.c