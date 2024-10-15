/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:57:30 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/15 16:57:40 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_command(char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(args[0], args);
		ft_putstr_fd("minishell: command not found\n", STDERR);
		exit(127);
	}
	else if (pid > 0)
	{
		g_sig.pid = pid;
		waitpid(pid, &(g_sig.exit_status), 0);
		g_sig.pid = 0;
		signal(SIGINT, sig_int);
		signal(SIGQUIT, sig_quit);
	}
}

void	ft_handle_child_process(pid_t pid)
{
	int	status;

	g_sig.pid = pid;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", STDERR);
			g_sig.exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDERR);
			g_sig.exit_status = 131;
		}
	}
	else if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	g_sig.pid = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
