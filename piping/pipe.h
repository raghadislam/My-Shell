#ifndef PIPE_H
#define PIPE_H

#define  MAX_ARGS 20
#define	 MAX_COMMAND_LENGTH 100

/* function to check if thee is a pipe operator | */
int check_for_pipe(char *cmd);

/* function to extract the two piped commands */
//void split_pipe_commands(char cmd[], char** first_cmd, char** second_cmd);

/* function to parse the command and extract arguments */
void parse_command(char *cmd, char **args);

/* function to execute the piping command */
void execute_piping(char cmd[]);

#endif
