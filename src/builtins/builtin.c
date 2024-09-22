#include "libft.h"
#include "builtin.h"
#include <stdbool.h>

int	length(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	run_builtin(const char **cargv, t_entab *table)
{
	int		errno;
	char	**argv;

	argv = (char **)cargv;
	errno = 0;
	if (ft_striccmp("echo", argv[0]) == 0)
		errno = echo(argv);
	else if (ft_striccmp("cd", argv[0]) == 0)
		errno = cd(argv, table);
	else if (ft_striccmp("pwd", argv[0]) == 0)
		errno = pwd(argv, table);
	else if (ft_striccmp("export", argv[0]) == 0)
		errno = ft_export(argv, table);
	else if (ft_striccmp("unset", argv[0]) == 0)
		errno = unset(argv, table);
	else if (ft_striccmp("env", argv[0]) == 0)
		errno = print_env(argv, table);
	else if (ft_striccmp("exit", argv[0]) == 0)
		errno = exit_sh(argv, table);
	return (errno);
}

bool	ft_isbuiltin(const char *command)
{
	return (ft_striccmp(command, "echo") == 0 || ft_striccmp(command, "cd") == 0
		|| ft_striccmp(command, "pwd") == 0 || ft_strcmp(command, "export") == 0
		|| ft_striccmp(command, "unset") == 0 || ft_striccmp(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0);
}
