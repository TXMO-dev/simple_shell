#include "main.h"

/**
 * execute_command - execute to output
 * @tokens: token
 * @num_tokens: number
 */
void execute_command(char **tokens, int num_tokens)
{
	pid_t pid;

	if (num_tokens == 0)
	{
		return;
	}
	if (strcmp(tokens[0], "exit") == 0)
	{
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
		execvp(tokens[0], tokens);
		perror("error");
		exit(1);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
