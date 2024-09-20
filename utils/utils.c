#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include "config.h"
#include "utils.h"


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


void split_commands(char *input, char **commands, int *num_commands)
{
    char *token;
    int i = 0;

    /* Use strtok to split the string by '&' */
    token = strtok(input, "&");
    while (token != NULL && i < MAX_COMMANDS) {
	/* Remove leading spaces */
	while (*token == ' ') {
	    token++;
	}

	/* Remove trailing spaces */
	char *end = token + strlen(token) - 1;
	while (end > token && *end == ' ') {
	    *end = '\0';
	    end--;
	}

	/* Store the command in the array */
	commands[i] = strdup(token);	// Duplicate the command string
	i++;
	token = strtok(NULL, "&");
    }

    /* Store the number of commands found */
    *num_commands = i;
}

/* function to parse the command and extract arguments */
void parse_command(char *cmd, char **args) {

	/* iterate till the last of the argumants */
    	for (int i = 0; i < MAX_ARGS; i++) {
        	args[i] = strsep(&cmd, " \t\r\n");
       		if (args[i] == NULL)
        		break;
		if((strcmp(args[i],">") == 0) || (strcmp(args[i],"2>") == 0) || (strcmp(args[i],"<") == 0))
		{
			args[i] = NULL;
			break;
		}
        	if (*args[i] == '\0')
            		i--;
    }
}

