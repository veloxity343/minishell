#include "libft.h"
#include "builtin.h"
#include <stdbool.h>

/*
@brief Counts the number of arguments in an array.
@param arg The array of arguments to count.
@details This function iterates through the array of strings (arguments) 
until it encounters a NULL value, counting the number of arguments.
@return The number of arguments in the array.
*/
int		arg_count(char **arg)
{
	int		size;

	size = 0;
	while (arg[size])
		size++;
	return (size);
}

/*
@brief Executes a built-in shell command if it matches a known command.
@param cargv The array of command-line arguments.
@param table A pointer to the environment variable table structure.
@details This function checks if the first argument is a known built-in shell command, 
such as "echo", "cd", or "pwd". If it matches, the corresponding function is called to execute the command.
@return An integer representing the status of the command execution, 0 on success, or an error code.
*/
int	run_builtin(const char **cargv, t_entab *table)
{
	int		errno;
	char	**argv;

	argv = (char **)cargv;
	errno = 0;
	if (ft_striccmp("echo", argv[0]) == 0)
		errno = ft_echo(argv);
	else if (ft_striccmp("cd", argv[0]) == 0)
		errno = ft_cd(argv, table);
	else if (ft_striccmp("pwd", argv[0]) == 0)
		errno = ft_export(argv, table);
	else if (ft_striccmp("export", argv[0]) == 0)
		errno = ft_export(argv, table);
	else if (ft_striccmp("unset", argv[0]) == 0)
		errno = ft_unset(argv, table);
	else if (ft_striccmp("env", argv[0]) == 0)
		errno = ft_print_env(argv, table);
	else if (ft_striccmp("exit", argv[0]) == 0)
		errno = ft_exit(argv, table);
	return (errno);
}

/*
@brief Checks if a given command is a built-in shell command.
@param command The command to check.
@details This function compares the input command with known built-in commands such as "echo", "cd", "pwd", etc.
@return True if the command is a built-in command, otherwise false.
*/
bool	ft_isbuiltin(const char *command)
{
	return (ft_striccmp(command, "echo") == 0 || ft_striccmp(command, "cd") == 0
		|| ft_striccmp(command, "pwd") == 0 || ft_strcmp(command, "export") == 0
		|| ft_striccmp(command, "unset") == 0 || ft_striccmp(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0);
}
