/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/10/15 22:09:30 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("trash ▸ ", STDERR);
		g_sig.exit_status = 1;
	}
	else
		kill(g_sig.pid, SIGINT);
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_sig.pid == 0)
		ft_putstr_fd("\b\b  \b\b", STDERR);
	else
	{
		kill(g_sig.pid, SIGQUIT);
		ft_putstr_fd("Quit: 3\n", STDERR);
		g_sig.exit_status = 131;
	}
	g_sig.sigquit = 1;
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
