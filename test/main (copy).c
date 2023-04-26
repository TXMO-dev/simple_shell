#include "main.h"

/**
 * main - main function
 * @argc: number of argument
 * @argv: argument
 * @environ: env variable
 * Return: 0
 */

int main(int argc, char **argv, char **environ)
{
	char *line = NULL ;
	char *delim = "\t \a\n";
	char *command;
	char **tokens;
	(void)argc;

	tokens = find_path(environ);

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		printf("$ ");
		line = read_line();
		argv = splits(line, delim);
		command = args_path(argv, tokens);
		if (command == NULL)
			execute(argv);
		free(line);
		free(argv);
		free(command);


		/*if (strcmp(argv[1], "exit") == 0)
		{
            		exit(0);
        	}
		else if (strcmp(argv[0], "env") == 0)
		{
            		char **env = environ;
           		while (*env)
			{
                		printf("%s\n", *env++);
            		}
           		 continue;
        	}*/
	}
	return (0);
}
