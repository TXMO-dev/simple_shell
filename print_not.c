#include "main.h"

char *name;
/**
 * print_not_found - prints when cmd is not found in path
 *
 * @cmd: a string provided by the stdin
 */
void print_not_found(char *cmd)
{
	write(2, name, _strlen(name));
	write(2, ": 1: ", 5);
	write(2, cmd, _strlen(cmd));
	write(2, ": not found\n", 12);
}
