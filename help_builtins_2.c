#include "shell.h"

void display_message(const char *message)
{
    write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_env - Displays information on the shell's built-in command 'env'.
 */
void help_env(void)
{
    const char *msg = "env: env\n\tPrints the current environment.\n";
    display_message(msg);
}

/**
 * help_setenv - Displays information on the shell's built-in command 'setenv'.
 */
void help_setenv(void)
{
    const char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";
    display_message(msg);
    msg = "environment variable, or modifies an existing one.\n\n";
    display_message(msg);
    msg = "\tUpon failure, prints a message to stderr.\n";
    display_message(msg);
}

/**
 * help_unsetenv - Displays information on the shell's built-in command 'unsetenv'.
 */
void help_unsetenv(void)
{
    const char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";
    display_message(msg);
    msg = "environmental variable.\n\n\tUpon failure, prints a ";
    display_message(msg);
    msg = "message to stderr.\n";
    display_message(msg);
}

