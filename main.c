#include "main.h"

/**
 * main - main function
 * @argc: number of argument
 * @argv: argument
 * @environ: env variable
 * Return: 0
 */
#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

int main(int argc, char **argv, char **environ)
{
	char cmd[MAX_CMD_LENGTH];
	char *args[MAX_ARGS];
	char *token;
	int num_args;
	pid_t pid;
	int bg = 0;
	
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


		// print prompt
        if (isatty(STDIN_FILENO)) {
            printf("$ ");
            fflush(stdout);
        }

        // read command from stdin
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL) {
            // exit on EOF
            break;
        }

        // check if command is running in the background
        bg = 0;
        if (cmd[strlen(cmd) - 2] == '&') {
            bg = 1;
            cmd[strlen(cmd) - 2] = '\0';
        }

        // parse command into arguments
        num_args = 0;
        token = strtok(cmd, " \t\n");
        while (token != NULL && num_args < MAX_ARGS - 1) {
            args[num_args++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[num_args] = NULL;

        // handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } else if (strcmp(args[0], "env") == 0) {
            char **env = environ;
            while (*env) {
                printf("%s\n", *env++);
            }
            continue;
        }

        // fork and execute command
        pid = fork();
        if (pid == 0) {
            // child process
            execvp(args[0], args);
            // if execvp returns, an error occurred
            perror(argv[0]);
            exit(1);
        } else if (pid < 0) {
            // fork error
            perror(argv[0]);
            exit(1);
        } else {
            // parent process
            if (!bg) {
                // wait for child process to finish
                waitpid(pid, NULL, 0);
            }
        }

	}
	return (0);
}
