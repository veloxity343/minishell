/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/10/12 18:29:00 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/define_lib.h"
#include "../inc/minishell.h"

int		global_sig = 0;

/*
signal handling part
control+c  = sigint
control+d = sigquit (EOF)end of file
using sigaction to ignore SIGINT and SIGQUIT

cause it's a void function
so i think the function should be completed
*/
void	ignore_signal(int sig)
{
		struct sigaction sa;

	while (sig == 1)
	{
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

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("minishell ▸ ", STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
