#ifndef UTILS_H
#define UTILS_H

/* function to print the prompt with the standard shell format */
void print_prompt(void);

/* function to extract the paralle commands */
void split_commands(char *input, char **commands, int *num_commands);

/* function to parse the command and extract arguments */
void parse_command(char *cmd, char **args);

#endif
