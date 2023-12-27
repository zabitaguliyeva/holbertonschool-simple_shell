#include "main.h"
<<<<<<< HEAD
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
=======
/**
 * main - main func
 *
 * Return: int
 */
int main(void)
{
>>>>>>> 33603554c8d8f732a549d927995ac83cac0660aa
    char *buff, **arr;
    int status, i;
    pid_t pid;

    while (1) {
        if (isatty(STDIN_FILENO))
            printf("$ ");
        buff = _getline();
        if (buff == NULL)
            break;
        arr = line_div(buff);
        free(buff);
        if (!*arr) {
            free(arr);
            continue;
        }
        if (strcmp(arr[0], "exit") == 0) {
            for (i = 0; *(arr + i); i++)
                free(*(arr + i));
            free(arr);
            break;
        }
        pid = fork();
        if (pid == 0) {
            if (execvp(arr[0], arr) == -1) {
                perror("ERROR");
<<<<<<< HEAD
                exit(2); 
            }
        } else if (pid > 0) {
            if (wait(&status) == -1) {
                perror("ERROR");
            }
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) != 0) {
                    exit(WEXITSTATUS(status));
                }
            }
        } else {
=======
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
>>>>>>> 33603554c8d8f732a549d927995ac83cac0660aa
            perror("ERROR");
        }
        if (pid == -1) {
            perror("ERROR");
        }
        for (i = 0; *(arr + i); i++)
            free(*(arr + i));
        free(arr);
    }
    return (0);
}
