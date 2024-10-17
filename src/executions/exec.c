/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:21 by chtan             #+#    #+#             */
/*   Updated: 2024/10/16 17:23:48 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"

/*
	requirement for execute
	1) token type
	2) command
	3) arguments
	
	when using exeve to execute, -1 will be error
	
	i think better put the exit at the function that call exec
	cause i also need to return the numbers.
	will need to exit with exit code 127 for command not found
*/
int	exec(char **array, char **envp)
{
	int num;
	int status;

	num = 0;
	status = 0;
	
	status = execve(array[num], array, envp);
	if (status == -1)
	{
		num = ft_dprintf(2, "command not found!");
		//exit_sig(0);
	}
	return (num);
}
