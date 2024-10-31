/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:00:00 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/27 14:52:47 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_sigint_handler(int signum, t_mini *mini)
{
	(void)signum;
	ft_clean_ms(mini);
	g_sig.heredoc_sigint = true;
	exit(SIGINT);
}

/*
@brief Executes heredoc functionality, reading input and writing to a pipe.
@param io The I/O node containing heredoc information.
@param p Pipe file descriptors used for heredoc.
@param mini The mini context for cleanup.
*/
void	ft_heredoc(t_io_node *io, int p[2], t_mini *mini)
{
	char	*line;
	char	*quotes;

	signal(SIGINT, (void *)ft_heredoc_sigint_handler);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(io->value, line))
			break ;
		if (!*quotes)
			ft_heredoc_expander(mini, line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
		free(line);
	}
	ft_clean_ms(mini);
	g_sig.exit_s = 0;
	exit(0);
}

/*
@brief Waits for heredoc child process and handles signal-based exits.
@param p Pipe file descriptors used for heredoc.
@param pid Pointer to the PID of the child process.
@param mini The mini context for cleanup.
@return true if heredoc was interrupted by SIGINT, false otherwise.
*/
static bool	ft_leave_leaf(int p[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, sig_quit);
	g_sig.heredoc_sigint = false;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

/*
@brief Initializes the execution of a leaf node (i.e., command or heredoc).
@param node The AST node representing the command to execute.
@param mini The mini context for cleanup.
*/
static void	ft_init_leaf(t_node *node, t_mini *mini)
{
	t_io_node	*io;
	int			p[2];
	int			pid;

	if (node->args)
		node->expanded_args = ft_expand(mini, node->args);
	io = node->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(p);
			g_sig.heredoc_sigint = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_heredoc(io, p, mini);
			if (ft_leave_leaf(p, &pid))
				return ;
			io->here_doc = p[0];
		}
		else
			io->expanded_value = ft_expand(mini, io->value);
		io = io->next;
	}
}

/*
@brief Initializes the execution tree, handling pipes and heredocs.
@param node The AST node representing the command tree to initialize.
@param mini The mini context for cleanup.
*/
void	ft_init_tree(t_node *node, t_mini *mini)
{
	if (!node)
		return ;
	if (node->type == N_PIPE)
	{
		ft_init_tree(node->left, mini);
		if (!g_sig.heredoc_sigint)
			ft_init_tree(node->right, mini);
	}
	else
		ft_init_leaf(node, mini);
}
