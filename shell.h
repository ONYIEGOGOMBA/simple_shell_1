#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

/* cmd.c */
int launch_command(char **);
int execute_shell(void);

/* forks.c */
int custom_shell(void);
int custom_launch(char **);

#endif /* SHELL_H */
