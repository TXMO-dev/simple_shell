#include "main.h"

/**
 * read_input - get input
 * @input_buffer: input
 */

void read_input(char *input_buffer)
{
	fgets(input_buffer, MAX_INPUT_SIZE, stdin);
	input_buffer[strcspn(input_buffer, "\n")] = 0;
}
