/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:57 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/15 21:23:58 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	ft_clean_ms();
	exit(SIGINT);
}

void	ft_heredoc(t_io_node *io, int p[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, ft_heredoc_sigint_handler);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_is_delimiter(io->value, line))
			break;
		if (!*quotes)
			ft_heredoc_expander(line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
		free(line);
	}
	ft_clean_ms();
	exit(0);
}

static bool	ft_leave_leaf(int p[2], int *pid, bool *sigint_child)
{
	int status;

	waitpid(*pid, &status, 0);
	*sigint_child = false;
	close(p[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
		return (true);
	return (false);
}
