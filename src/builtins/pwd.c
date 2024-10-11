#include "minishell.h"

/*
@brief Prints the current working directory.
@details This function retrieves the current working directory using the `getcwd` 
system call and prints it to standard output. If the retrieval fails, it returns 1 
to indicate an error.
@return Returns 0 on success, or 1 on failure.
*/
int		ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}
