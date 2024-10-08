# My Shell

a custom Unix-like shell implemented in C that provides a number of built-in commands, supports external commands execution, commands redirection, and variables assigning and exporting.

## Features

- **supports both interactive mode and batch mode:** the shell is able to read scripts or take commands line by line from the user.
- **Execute External Commands:** Run standard Unix commands directly from the shell.
- **Commands Redirection:** Redirect the commands input, output and error using `<`, `>`, and `2>` respectively.
- **Commands Piping:** Pipe the commands using the pipe operator `|`.
- **Variable Assignment:** Assign and store variables using `VAR=value`.
- **Export Variables:** Use the `export` command to make variables available as environment variables.
- **Built-in Commands:**
  - `mycp`: Copy files (similar to `cp`).
  - `mypwd`: Print the current working directory (similar to `pwd`).
  - `mymv`: Move or rename files (similar to `mv`).
  - `myecho`: Display a line of text or the value of a variable (similar to `echo`).
  - `mygrep`: Search for a pattern in a file (similar to `grep`).
  - `mycat`: Concatenate and display file contents (similar to `cat`).

## Installation

Clone the repository and compile the shell:
To compile `MyShell` with its various source files, use the following `gcc` command: 
  ```bash
git clone https://github.com/your-username/my-custom-shell.git
```
```bash
gcc -o myshell *.c */*.c
```
```bash
./myshell
```
## Examples 

### work in batch mode
```bash
./myshell batch.txt
```

### Copying a File
```bash
mycp file1.txt file2.txt
```

### Moving a File
```bash
mymv file1.c file2.c
```

### Printing the Current Directory
```bash
mypwd
```

### Assigning and exporting a variable
```bash
 VAR=9
```
```bash
 export VAR
```
```bash
 env
```

### Echoing a Message or a variable
```bash
 myecho "Hello, world!"
```
```bash
 myech $VAR
```

### redirection an input, output and error
  ```bash
 ls -l > list.txt
```
  ```bash
 cat < script.txt
```
  ```bash
 lssss 2> error.txt
```
### piping commands
  ```bash
 ls -l | grep comm
```
### execute parallel commands
```bash
cmd1 & cmd2 & cmd3
```
