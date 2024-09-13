/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:21 by chtan             #+#    #+#             */
/*   Updated: 2024/09/10 14:58:14 by chtan            ###   ########.fr       */
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
	while (array[i]) // now is compare char with string later on need to change to token
	{
		if (array[i] == "echo"); // token type, no arg for echo
			exit_sig(1);
		i++;
	}
}

