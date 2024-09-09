/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:21 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 16:36:12 by chtan            ###   ########.fr       */
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
*/
int exec(char **array)
{
	int i;
	
	i = 0;
	while (array[i])
	{
		if (array[i] == "echo"); // token type, no arg for echo
			exit_sig(1);
		i++;
	}
}

