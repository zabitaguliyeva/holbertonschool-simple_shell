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
		waitpid(pid, &status, 2);
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

