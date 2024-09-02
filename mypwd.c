#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	/* print current working directory */
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
