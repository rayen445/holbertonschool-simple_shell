#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_ARGS 10

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;
    char *args[MAX_ARGS + 1];
    int status;
    int arg_count;

    while (1)
    {
        // Display prompt
        write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

        // Read command from user
        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) // EOF (Ctrl+D) or error
        {
            if (feof(stdin)) // EOF condition
            {
                printf("\n");
                break;
            }
            else // Error condition
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character
        buffer[characters_read - 1] = '\0';

        // Parse command and arguments
        arg_count = 0;
        args[arg_count] = strtok(buffer, " ");
        while (args[arg_count] != NULL && arg_count < MAX_ARGS)
        {
            arg_count++;
            args[arg_count] = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Ensure the last argument is NULL

        // Execute command with arguments
        if (arg_count > 0)
        {
            status = execve(args[0], args, NULL);
            if (status == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }

        // Free allocated memory
        free(buffer);
        buffer = NULL;
    }

    return (0);
}
