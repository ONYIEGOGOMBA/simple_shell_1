#include "shell.h"
/**
 * execute_shell - start of the code
 * Return: Returns status
 */
int execute_shell(void)
{
	char input[MAX_INPUT_SIZE];
	int status;
	char *tokens[MAX_INPUT_SIZE];
	int token_count = 0;
	char *token = strtok(input, " ");

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

		while (token != NULL)
		{
			tokens[token_count++] = token;
			token = strtok(NULL, " ");
		}
		tokens[token_count] = NULL;

		if (token_count > 0)
		{
			status = launch_command(tokens);
		}
	}
	return (status);
}
/**
 * launch_command - it launches the command
 * @args: variable
 * Return: returns the status
 */
int launch_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	} else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	} else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
