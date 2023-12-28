#include "main.h"
/**
 * main - main func
 *
 * Return: int
 */
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
				exit(status);
			}
		}
		else if (pid > 0)
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("ERROR");
			}
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				if (status == 127)
				{
					exit(status);
				}
			}
		}
		else
		{
			perror("ERROR");
		}
		if (pid == -1)
		{
			perror("ERROR");
		}
		for (i = 0; *(arr + i); i++)
			free(*(arr + i));
		free(arr);
	}
	return (0);
}
