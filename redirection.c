#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "redirection.h"

int check_for_redirection(char cmd[])
{
	/* copy the original command */
	char cmd2[100]; char cmd3[100];
	strcpy(cmd2, cmd); strcpy(cmd3, cmd);

	/* check for '>' output director */
	char* outputRed_occurrence = strchr(cmd, '>');
	if(outputRed_occurrence)
	{
		char* filename = strsep(&outputRed_occurrence, " \t\r\n");
		filename = strsep(&outputRed_occurrence, " \t\r\n");
		if(strlen(filename) == 0 || filename == NULL)
		{
			printf("error: no file to redirect output to\n");
			return -1;
		}
		int fd = open(filename, O_WRONLY|O_CREAT, 0644);
		if(fd == -1)
		{
			printf("open error\n");
			return -1;
	}
		dup2(fd,1);
		close(fd);
	}

	/* check for '2>' error director */
	char* errorRed_occurrence = strstr(cmd2, "2>");
	if(errorRed_occurrence)
	{
		char* filename = strsep(&errorRed_occurrence, " \t\r\n");
		filename = strsep(&errorRed_occurrence, " \t\r\n");
		if(strlen(filename) == 0 || filename == NULL)
		{
			printf("error: no file to redirect error to\n");
			return -1;
		}
		int fd = open(filename, O_WRONLY|O_CREAT, 0644);
		if(fd == -1)
		{
			printf("open error\n");
			return -1;
		}
		dup2(fd,2);
		close(fd);
	} 

	/* check for '<' input director */
	char* inputRed_occurrence = strchr(cmd3, '<');
	if(inputRed_occurrence)
	{
		char* filename = strsep(&inputRed_occurrence, " \t\r\n");
		filename = strsep(&inputRed_occurrence, " \t\r\n");
		if(strlen(filename) == 0 || filename == NULL)
		{
			printf("error: no file to redirect input from\n");
			return -1;
		}
		int fd = open(filename, O_RDONLY, 0644);
		if(fd == -1)
		{
			printf("open error\n");
			return -1;
		}
		dup2(fd,0);
		close(fd);
	}

	return 1;

}




