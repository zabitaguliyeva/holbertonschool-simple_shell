#include "main.h"
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *buff, **arr;
    int status, i;
    pid_t pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");
        buff = _getline();
        if (buff == NULL)
            break;
        arr = line_div(buff);
        free(buff);
        if (!*arr)
        {
            free(arr);
            continue;
        }
        if (strcmp(arr[0], "exit") == 0)
        {
            for (i = 0; *(arr + i); i++)
                free(*(arr + i));
            free(arr);
            break;
        }
        else if (strcmp(arr[0], "env") == 0)
        {
            print_environment();
            for (i = 0; *(arr + i); i++)
                free(*(arr + i));
            free(arr);
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            if (execvp(arr[0], arr) == -1)
            {
                perror("ERROR");
                exit(1);
            }
        }
        else if (pid > 0)
        {
            if (wait(&status) == -1)
            {
                perror("ERROR");
            }
        }
        else
            perror("ERROR");
        if (pid == -1)
            perror("ERROR");
        for (i = 0; *(arr + i); i++)
            free(*(arr + i));
        free(arr);
    }
    return (0);
}

