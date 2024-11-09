/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:01 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:32:11 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Executes the child process for pipes, handling left and right dirs.
@param mini The shell context (contains environment, AST, etc.).
@param node The node to execute.
@param pfds The pipe file descriptors.
@param dir The direction of the pipe (TD_LEFT or TD_RIGHT).
@details Handles the redirection of standard input and output for pipes.
@return void
*/
static void	ft_exec_pipe_child(t_mini *mini, t_node *node, int pfds[2],
		t_ast_dir dir)
{
	int	status;

	status = 0;
	if (dir == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (dir == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = ft_exec_node(mini, node, true);
	ft_clean_ms(mini);
	exit(status);
}

/*
@brief Returns the correct exit status based on signal handling or exit code.
@param status The status from waitpid.
@return The exit status code.
*/
int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

/*
@brief Executes a pipeline of commands represented by a tree structure.
@param mini The shell context (contains environment, AST, etc.).
@param node The root node of the pipeline.
@return The exit status of the last executed command or an error code.
*/
static int	ft_exec_pipeline(t_mini *mini, t_node *node)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_sig.sigint = true;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(mini, node->left, pfds, TD_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_child(mini, node->right, pfds, TD_RIGHT);
		else
		{
			(close(pfds[0]), close(pfds[1]), waitpid(pid_l, &status, 0),
				waitpid(pid_r, &status, 0));
			g_sig.sigint = false;
			return (ft_get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

/*
@brief Executes a node (command or pipeline) from the AST.
@param mini The shell context (contains environment, AST, etc.).
@param node The node to execute.
@param piped Indicates whether the node is part of a pipeline.
@details Handles the execution of simple commands and pipelines.
@return The status of the execution.
*/
int	ft_exec_node(t_mini *mini, t_node *node, bool piped)
{
	if (!mini->ast)
		return (1);
	if (node->type == N_PIPE)
		return (ft_exec_pipeline(mini, node));
	else
		return (ft_exec_simple_cmd(mini, node, piped));
}
