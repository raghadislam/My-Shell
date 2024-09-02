#include <stdio.h>

int main(int argc, char* argv[])
{
	/* print all arguments taken */
	if(argv != NULL)
	{
		for(int i = 1; i < argc; i++)
		{
			printf("%s ",argv[i]);
		}
	}
	printf("\n");
}
