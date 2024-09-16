#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include "piping/pipe.h"
#include "shell_variables/shell_variables.h"
#include "internal_commands/internal_command.h"
#include "external_commands/external_command.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 20

/* the command will be taken from the user */
char cmd[MAX_COMMAND_LENGTH];

/* arguments array */
char *args[MAX_ARGS];

/* array to store shell variables */
shell_var ShellVariables[MAX_VAR];


/* function to print the prompt with the standard shell format */
void print_prompt(void)
{
	char* username;
	char hostname[100];
	char cwd[100];
	username = getpwuid(getuid())->pw_name;
	gethostname(hostname,100);
	getcwd(cwd,100);
	printf("\033[1;34m%s@%s\033[0m:\033[1;32m%s\033[0m$ ", username, hostname, cwd);
}


/* environment variables */
extern char **environ;

int main(int argc, char*argv[])
{

	while(1)
	{   
		/* printnig the prompt of the shell */
		print_prompt();

		/* Exit if user hits EOF (Ctrl+D) */
		if(fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		

		/* remove the newline character from the input */
		int len = strlen(cmd);
		cmd[len - 1] = 0;

		/* copy the full command to save it and manipulate the original */
		char cmd2[MAX_COMMAND_LENGTH];
		strcpy(cmd2,cmd);

		/* Ignore empty commands */
		if(cmd[0] == 0) continue;

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

		/* check for exit command */
		if(strcmp(cmd,"exit") == 0)
		{
			break;
		}
		
		/* check for my internal shell commands */
		if(check_for_internal_command(cmd, args) == 1) continue;

		/* execute the external command */
		if(execute_external(cmd,args,environ,cmd2)) return -1;
	}
	return 0;
}
