# My Shell

a custom Unix-like shell implemented in C that provides a number of built-in commands, supports external commands execution, commands redirection, and variables assigning and exporting.

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
To compile `MyShell` with its various source files, use the following `gcc` command: 
  ```
git clone https://github.com/your-username/my-custom-shell.git
gcc -o myshell *.c */*.c
./myshell
```
## Examples 

### Copying a File
```
mycp file1.txt file2.txt
```

### Moving a File
```
mymv file1.c file2.c
```

### Printing the Current Directory
```
mypwd
```

### Assigning and exporting a variable
```
 VAR=9
```
```
 export VAR
```
```
 env
```

### Echoing a Message or a variable
```
 myecho "Hello, world!"
```
```
 myech $VAR
```

### redirection an input, output and error
```
 ls -l > list.txt
 ```
```
 cat < script.txt
```
```
 lssss 2> error.txt
```
