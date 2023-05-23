#include "shell.h"

/**
 * main - Entry point for the custom shell program.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read;

	if (ac < 1)
		return (1);

	name = get_location(av[0]);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	while (1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		read = _getline(&line, &bufsize, stdin);
		if (read == END_OF_FILE)
			break;
		if (read == -1)
		{
			free(line);
			line = NULL;
			continue;
		}
		handle_line(&line, read);
	}

	free(line);
	free_env();
	free_alias_list(aliases);
	return (0);
}

/**
 * handle_line - Handles a line of input from the user.
 * @line: Pointer to the line of input.
 * @read: Number of characters read.
 */
void handle_line(char **line, ssize_t read)
{
	int exe_ret = 0;
	char **args = NULL;
	char **front = NULL;

	if ((*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';

	args = _strtok(*line, " \t\n");
	if (args == NULL)
	{
		free(*line);
		return;
	}

	variable_replacement(args, &exe_ret);
	front = args;
	if (exe_ret != EXIT)
		exe_ret = handle_args(&exe_ret);

	free_args(args, front);
	free(*line);
	*line = NULL;
}

