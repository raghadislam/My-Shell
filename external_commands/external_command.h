#ifndef EXTI_CMD
#define EXTI_CMD

/* function to execute any external commands that exist in the PATH environment variable */
int execute_external(char cmd[], char* args[], char** environ, char cmd2[]);

#endif
