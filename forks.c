#include "shell.h"
/**
 * execute_shell - it executes the shell
 * Return: returns the status
 */
int custom_shell(void)
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
 * launch_command - launcher command
 * @args: variable
 * Return: Returns exit status
 */
int custom_launch(char **args)
{
	pid_t pid;
	int status;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *path_token = strtok(path_copy, ":");
	char cmd_path[MAX_INPUT_SIZE];
	int cmd_found = 0;

	while (1)
	{
		while (path_token != NULL)
		{
			snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_token, args[0]);
			if (access(cmd_path, X_OK) == 0)
			{
				cmd_found = 1;
				break;
			}
			path_token = strtok(NULL, ":");
		}
		if (!cmd_found)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			free(path_copy);
			return (EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(path_copy);
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execv(cmd_path, args) == -1)
			{
				perror(args[0]);
				free(path_copy);
				exit(EXIT_FAILURE);
			}
		} else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				free(path_copy);
				return (EXIT_FAILURE);
			}
			free(path_copy);
			return (EXIT_SUCCESS);
		}
	}
}
