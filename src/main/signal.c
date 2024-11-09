/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:33:58 by chtan             #+#    #+#             */
/*   Updated: 2024/11/09 10:02:55 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Signal handler for SIGINT.
@param num Signal number.
@return Signal and exit status; return carriage & newline.
*/
void	sig_int(int num)
{
	(void)num;
	if (g_sig.sigint)
	{
		ft_putstr_fd("\n", 1);
		g_sig.sigint = false;
		g_sig.heredoc_sigint = true;
		g_sig.exit_s = 130;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
@brief Signal handler for SIGQUIT.
@param num Signal number.
@return Exit status; print Quit message.
*/
void	sig_quit(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
	g_sig.exit_s = 131;
}

/*
@brief Initializes signal handling.
@details Disables ECHOCTL for terminal to prevent
	printing of SIGINT. Sets signal based on terminal input.
@return None.
*/
void	sig_init(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_sig.heredoc_sigint = false;
	g_sig.sigint = false;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
