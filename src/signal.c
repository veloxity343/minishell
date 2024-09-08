/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/09/08 15:11:47 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/temp.h"
/*
signal handling part
control+c  = sigint
control+d = sigquit (EOF)end of file
*/
void	ignore_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	exit_sig(int sig)
{
	if (EXIT_SUCCESS == sig)
	{
		ft_printf("exit\n");
		exit(1);
	}
	if (sig == EXIT_FAILURE)
	{
		ft_printf("\n");
		exit(1);
	}
}
