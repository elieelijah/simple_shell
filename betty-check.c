#include "shell.h"

/**
 * main - Entry point of the simple shell program
 * @argc: The number of arguments passed to the program
 * @argv: An array of strings containing the arguments
 * @envp: An array of strings containing the environment variables
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *envp[])
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read;
	char **args, **front;
	int exe_ret = 0;

	(void)argc;
	name = argv[0];
	environ = envp;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		read = _getline(&line, &bufsize, stdin);

		if (read == END_OF_FILE)
			break;
		handle_line(&line, read);
		args = _strtok(line, " \t\r\n");
		front = args;
		variable_replacement(args, &exe_ret);
		if (call_args(args, &front, &exe_ret) == EXIT)
		{
			free_args(args, front);
			free(line);
			free_env();
			exit(exe_ret);
		}
		free_args(args, front);
		free(line);
		hist++;
	}
	free_env();
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	return (exe_ret);
}
