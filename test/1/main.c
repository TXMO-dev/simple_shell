#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/* Function prototypes */
char **parse_input(char *input);
int execute_command(char **args);

/**
 * main - Entry point of the program
 *
 * Return: Always 0 on success
 */
int main(void)
{
    char *input;
    char **args;
    int status;

    do {
        printf("$ ");
        input = malloc(BUFFER_SIZE);
        if (!input)
        {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }

        if (fgets(input, BUFFER_SIZE, stdin) == NULL)
        {
            free(input);
            exit(EXIT_SUCCESS);
        }

        args = parse_input(input);
        status = execute_command(args);

        free(input);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}

/**
 * parse_input - Parse the user input
 * @input: The input string to parse
 *
 * Return: An array of strings containing the parsed input
 */
char **parse_input(char *input)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tokens)
            {
                perror("realloc error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

/**
 * execute_command - Execute a command with the given arguments
 * @args: An array of strings containing the command and its arguments
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
    {
        return 1;
    }

    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "cd: expected argument to \"cd\"\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("chdir error");
            }
        }
        return 1;
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork error */
        perror("fork error");
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
