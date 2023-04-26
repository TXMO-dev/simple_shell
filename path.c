#include "main.h"

/**
 * find_path - find the path
 * @environ: env variable
 * Return: path 
 */

char **find_path(char **environ)
{
	char *get_path, **tokens, *delim;

	delim = ":";
	get_path = _getenv(environ, "PATH");
	tokens = splits(get_path, delim);
	return (tokens);
}
