#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "external_command.h"
#include "redirection.h"


int execute_external(char cmd[], char* args[], char** environ, char cmd2[])
{
	/* fork the current process */
	int ret_pid = fork();

	/* check the return value of fork */
	if(ret_pid < 0)
	{
		/* announce that fork failed */
		printf("fork faild\n");
		return -1;
	}
	else if(ret_pid > 0) /* in the parent process */
	{
		/* wait for the change in the status of the child */
		int state;
		wait(&state);
		return 0;
	}
	else if(ret_pid == 0) /* in the child process */
	{	
		check_for_redirection(cmd2);
		/* execute the command taken from the user*/
		execvpe(cmd, args, environ);
		printf("error: command not found\n");
		return -1;
	}

}


