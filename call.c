#include "main.h"

/**
 * call_command - calls cmd, forks, execve
 *
 * @cmd_arr: a string provided by the stdin
 * Return: 0
 */

int call_command(char *cmd_arr[])
{
	char *exe_path_str = NULL;
	char *cmd = NULL;
	pid_t is_child;
	int status;

	cmd = cmd_arr[0];
	exe_path_str = pathfinder(cmd);
	if (exe_path_str == NULL)
	{
		print_not_found(cmd);
		return (3);
	}
	is_child = fork();
	if (is_child < 0)
	{
		perror("Error:");
		return (-1);
	}
	if (is_child > 0)
		wait(&status);
	else if (is_child == 0)
	{
		(execve(exe_path_str, cmd_arr, environ));
		perror("Error:");
		exit(1);
	}
	free(exe_path_str);
	return (0);
}
