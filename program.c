#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include "shell_variables.h"
#include "external_command.h"

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


/* function to parse the command and extract arguments */
void parse_command(char *cmd, char **args) {

    	for (int i = 0; i < MAX_ARGS; i++) {
        	args[i] = strsep(&cmd, " \t\r\n");
       		if (args[i] == NULL)
        		break;
        	if (*args[i] == '\0')
            		i--;
    }
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

		/* Ignore empty commands */
		if(cmd[0] == 0) continue;

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

		/* execute the external command */
		if(execute_external(cmd,args,environ)) return -1;
	}
	return 0;
}
