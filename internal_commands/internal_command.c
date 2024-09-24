#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "internal_command.h"

int number_of_args(char* args[])
{
	int counter = 0;
	while(args[counter])
	{
		counter++;
	}
	return counter;
}

int check_for_internal_command(char cmd[], char* argv[])
{
	int argc = number_of_args(argv);

	if(strcmp(cmd,"mycp") == 0)
	{
		mycp(argc, argv);
		return 1;
	}

	else if(strcmp(cmd,"myecho") == 0)
	{
		myecho(argc, argv);
		return 1;
	}
	else if(strcmp(cmd,"mymv") == 0)
	{
		mymv(argc, argv);
		return 1;
	}
	else if(strcmp(cmd,"mypwd") == 0)
	{
		mypwd();
		return 1;
	}
	else if(strcmp(cmd,"mycat") == 0)
	{
		mycat(argc, argv);
		return 1;
	}
	else if(strcmp(cmd,"mygrep") == 0)
	{
		mygrep(argc, argv);
		return 1;
	}
	else if (strcmp(cmd, "cd") == 0)
	{
		if (argc != 2 || chdir(argv[1]) == -1)
		{
		    printf("cd: error\n");
		    exit(0);
		}
		return 1;
  	}


	return 0;
}
