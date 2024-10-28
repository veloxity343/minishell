/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:47:41 by chtan             #+#    #+#             */
/*   Updated: 2024/10/28 12:47:43 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Prints the current working directory.
@details This function retrieves the current working directory using the `getcwd`
system call and prints it to standard output. If the retrieval fails,
	it returns 1
to indicate an error.
@return Returns 0 on success, or 1 on failure.
*/
int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (1);
	ft_putendl_fd(cwd, STDOUT);
	return (0);
}
