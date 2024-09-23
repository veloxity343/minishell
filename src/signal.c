/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/09/23 13:58:40 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
/*
signal handling part
control+c  = sigint
control+d = sigquit (EOF)end of file
using sigaction to ignore SIGINT and SIGQUIT

cause it's a void function
so i think the function should be completed
*/
void ignore_signal(int sig)
{
	while (sig == 1)
	{
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}

/*
from a senior cadet the global sig is not working cause this is
in a child process. so i need to pass it to the main.
*/
void	exit_sig(int sig)
{
	if (EXIT_SUCCESS == sig)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (sig == EXIT_FAILURE)
	{
		ft_printf("\n");
		global_sig = 1;
		exit(1);
	}
}
