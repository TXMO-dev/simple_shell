#include "main.h"

/**
 * cmd_read - handles command line and tokenizes it
 * @s: string
 * @file_stream: getline input
 * Return: 0
 */
int cmd_read(char *s, size_t __attribute__((unused))file_stream)
{
	char *token = NULL;
	char *cmd_arr[100];
	int i;

	if (_strcmp(s, "exit") == 0)
		return (2);
	if (_strcmp(s, "env") == 0)
		return (_printenv());
	token = strtok(s, " "), i = 0;
	while (token)
	{
		cmd_arr[i++] = token;
		token = strtok(NULL, " ");
	}
	cmd_arr[i] = NULL;

	return (call_command(cmd_arr));
}
