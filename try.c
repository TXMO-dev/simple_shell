#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64
extern char **environ;

int main(void) {
    char cmd[MAX_CMD_LENGTH];
    char *args[MAX_ARGS];
    char *token;
    int num_args;
    pid_t pid;
    int bg = 0;

    while (1) {

        printf("$ ");
        fflush(stdout);


        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL) {
            break;
        }


        bg = 0;
        if (cmd[strlen(cmd) - 2] == '&') {
            bg = 1;
            cmd[strlen(cmd) - 2] = '\0';
        }


        num_args = 0;
        token = strtok(cmd, " \t\n");
        while (token != NULL && num_args < MAX_ARGS - 1) {
            args[num_args++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[num_args] = NULL;


        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } 

        else if (strcmp(args[0], "env") == 0) {
            char **env = environ;
            while (*env) {
                printf("%s\n", *env++);
            }
            continue;
        } 

        else {
            pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror(args[0]);
                exit(1);
            } else if (pid < 0) {
                perror("fork");
                exit(1);
            } else {
                if (!bg) {
                    waitpid(pid, NULL, 0);
                }
            }
        }
    }

    return 0;
}

