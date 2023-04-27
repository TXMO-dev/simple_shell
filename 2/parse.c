#include "main.h"

/**
 * parse_input - parse input
 * @input_buffer: input
 * @tokens: token
 * @num_tokens: number
 */

void parse_input(char *input_buffer, char **tokens, int *num_tokens)
{
	char *token = strtok(input_buffer, " ");

	while (token != NULL && *num_tokens < MAX_NUM_TOKENS)
	{
	tokens[(*num_tokens)++] = token;
	token = strtok(NULL, " ");
	}
	tokens[*num_tokens] = NULL;
}
