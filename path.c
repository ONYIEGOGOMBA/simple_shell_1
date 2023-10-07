#include "shell.h"
#include <stdlib.h>
/**
 * main - start of the command line
 * Return: reaturns 0
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	pid_t pid;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			char *args[2];

			args[0] = input;
			args[1] = NULL;
			execve(input, args, environ);
			perror(input);
			exit(EXIT_FAILURE);
		} else
		{
			int status;

			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (0);
}
