#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int custom_exit(char **args, char **front);
int custom_cd(char **args, char __attribute__((__unused__)) **front);
int custom_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding
 *               custom shell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", custom_exit },
		{ "env", custom_env },
		{ "setenv", custom_setenv },
		{ "unsetenv", custom_unsetenv },
		{ "cd", custom_cd },
		{ "alias", custom_alias },
		{ "help", custom_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * custom_exit - Causes normal process termination
 *                for the custom shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int custom_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (handle_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (handle_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_alias_list(aliases);
	exit(num);
}

/**
 * custom_cd - Changes the current directory of the custom shell process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat dir;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
			handle_cd_special_cases(args, old_pwd);
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(old_pwd);
				return (handle_error(args, 2));
			}
		}
	}
	else
	{
		handle_cd_home(old_pwd);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = old_pwd;
	if (custom_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (custom_setenv(dir_info, dir_info) == -1)
		return (-1);

	handle_cd_print(args, pwd, new_line, old_pwd, pwd);

	return (0);
}

/**
 * custom_help - Displays information about custom shell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

