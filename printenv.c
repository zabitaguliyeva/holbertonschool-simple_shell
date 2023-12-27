#include "main.h"
/**
 * print_environment - delimited string input
 * Return: NULL
 */
void print_environment() {
    extern char **environ;
    char **env_var = environ;
    while (*env_var != NULL) {
        printf("%s\n", *env_var);
        env_var++;
    }
}
