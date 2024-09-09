/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:35:19 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 17:20:14 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"

void	error_msg(char *msg)
{
	ft_printf("\033[31mError\033[0m");
	ft_dprintf(1, ": %s\n", msg);
	exit_sig(1);
}
/*
while command not defined
when i test this case, the (echo $?) didn't give me error
*/
void undefined_message(char *command)
{
	ft_printf("bash: %s: command not found\n", command);
	exit_sig(1);
}

/*
where you key in exti it should really exit our minibash
*/
void	real_exit(void)
{
	ft_printf("exit\n");
	exit(0);
}