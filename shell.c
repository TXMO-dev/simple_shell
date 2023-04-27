#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

/**
 * main - entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
    char *command;
    size_t command_size = 0;
    ssize_t command_len;

    while (1)
    {
        printf("%s", PROMPT);

        command_len = getline(&command, &command_size, stdin);
        if (command_len == -1)
            break;

        command[command_len - 1] = '\0'; /* Remove the newline character */

        if (access(command, X_OK) == 0)
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                char *argv[2];
                argv[0] = command;
                argv[1] = NULL;
                execve(command, argv, NULL);
                perror("Execve failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                int status;
                if (wait(&status) == -1)
                {
                    perror("Wait failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            fprintf(stderr, "%s: command not found\n", command);
        }
    }

    free(command);
    return (0);
}
