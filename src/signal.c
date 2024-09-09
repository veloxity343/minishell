/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/09/09 15:45:16 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
int global_sig = 0;
/*
signal handling part
control+c  = sigint
control+d = sigquit (EOF)end of file
*/
void ignore_signal(void)
{
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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
≈		exit(1);
	}
	if (sig == EXIT_FAILURE)
	{
		ft_printf("\n");
		global_sig = 1;
		exit(1);
	}
}
