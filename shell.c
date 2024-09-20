#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include "utils/config.h"
#include "utils/utils.h"
#include "piping/pipe.h"
#include "shell_variables/shell_variables.h"
#include "internal_commands/internal_command.h"
#include "external_commands/external_command.h"

/* the command will be taken from the user */
char* input = NULL;
size_t size = MAX_COMMAND_LENGTH;

/* array to store pid of all processes */
int pid[MAX_COMMANDS];

/* arguments array */
char *args[MAX_ARGS];

/* array to store shell variables */
shell_var ShellVariables[MAX_VAR];

/* environment variables */
extern char **environ;

int main(int argc, char*argv[])
{
	/* check the right use of the shell */
	if (argc > 2)
	{
		printf("error: my shell takes only one file\n");
		exit(1);
	}

	/* check which mode to run, interactive mode or batch mode */
	FILE *fp;
	if (argc == 1)
	{
		fp = stdin;
		print_prompt();
	}
	else
	{
		fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("error: can't open the file\n");
			exit(1);
		}
	}

	while(getline(&input, &size, fp) != EOF)
	{   
		/* remove the newline character from the input */
		int len = strlen(input);
		input[len - 1] = 0;

		/* check for exit command */
		if(strcmp(input,"exit") == 0)
		{
			break;
		}

		if (fp == stdin)
		{
			/* printnig the prompt of the shell */
			print_prompt();
		}

		/* Ignore empty commands */
		if(input[0] == 0) continue;

		int num_commands = 0;
		char *commands[MAX_COMMANDS];
		int is_parallel = 0;
		
		/* check the number of parallel process*/
		if (strstr(input, "&") != NULL)
		{
			split_commands(input, commands, &num_commands);
			is_parallel = 1;
		}
		else
		{
			num_commands = 1;
			commands[0] = input;
			is_parallel = 0;
		}

		for (int i = 0; i < num_commands; i++) {

	    		/* copy the full command to save it and manipulate the original */
			char cmd[MAX_COMMAND_LENGTH];
			strcpy(cmd, commands[i]);
			char cmd2[MAX_COMMAND_LENGTH];
			strcpy(cmd2,cmd);
	
			if(check_for_pipe(cmd))
			{
				/* exeute the piping commands then continue */
				execute_piping(cmd);
				continue;
			}

			/* check for '=' appearence */
			if(check_for_equal(cmd, ShellVariables)) continue;

			/* parse the input */
			parse_command(cmd, args);

			/* substitute any accessed variables with their values*/
			substitute_var(args, ShellVariables);
		
			/* check for "expoert" command */
			if(check_for_export(args, ShellVariables)) continue;

			/* check for my internal shell commands */
			if(check_for_internal_command(cmd, args) == 1) continue;

			/* execute the external command */
			if(execute_external(cmd, args, environ, cmd2, pid, i, is_parallel)) return -1;
		}
		/* wait for the zombie processes */
		wait_for_processes(pid, num_commands);

	}
	return 0;
}
