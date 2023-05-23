#include "shell.h"

/**
 * display_message - Displays message on the shellby builtin command.
 */

void display_message(const char *msg)
{
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	const char *msg = "env: env\n\tPrints the current environment.\n";

	display_message(msg);
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
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
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
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

