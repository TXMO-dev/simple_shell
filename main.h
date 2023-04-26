#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

void print_prompt();
void read_input(char* input_buffer);
void parse_input(char* input_buffer, char** tokens, int* num_tokens);
void execute_command(char** tokens, int num_tokens);


#endif
