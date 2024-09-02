# My Custom Shell

A simple shell implemented in C that supports executing external commands, storing and exporting variables, and includes several built-in commands.

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
cd my-custom-shell
gcc -o my_shell my_shell.c

