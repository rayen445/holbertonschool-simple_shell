#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROMPT "#cisfun$ "

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
    int status;

    while (1)
    {
        /* Display prompt */
        write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

        /* Read command from user */
        characters_read = getline(&buffer, &bufsize, stdin);
        if (characters_read == -1) /* EOF (Ctrl+D) or error */
        {
            if (feof(stdin)) /* EOF condition */
            {
                printf("\n");
                break;
            }
            else /* Error condition */
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        /* Remove newline character */
        buffer[characters_read - 1] = '\0';

        /* Execute command */
        status = system(buffer);
        if (status == -1)
        {
            perror("system");
            exit(EXIT_FAILURE);
        }

        /* Free allocated memory */
        free(buffer);
        buffer = NULL;
    }

    return (0);
}
