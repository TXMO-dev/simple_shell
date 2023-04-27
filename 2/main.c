#include "main.h"

/**
 * main - main function
 * Return: nothing
 */

int main(void)
{
	char input_buffer[MAX_INPUT_SIZE];
	char *tokens[MAX_NUM_TOKENS];
	int num_tokens = 0;

	while (1)
	{
	print_prompt();
	read_input(input_buffer);
	parse_input(input_buffer, tokens, &num_tokens);
	execute_command(tokens, num_tokens);
	num_tokens = 0;
	}
	return (0);
}
