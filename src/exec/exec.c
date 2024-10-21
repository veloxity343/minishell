/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:01 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 17:15:46 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Executes the child process for pipes, handling left and right dirs.
@param node The AST node representing the command to execute.
@param pfds The pipe file descriptors.
@param dir The direction of the pipe (TD_LEFT or TD_RIGHT).
*/
static void	ft_exec_pipe_child(t_node *node, int pfds[2], t_ast_dir dir)
{
	int	status;

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
	status = ft_exec_node(node, true);
	ft_clean_ms(node);
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
@brief Forks a child process to execute a command
	in the right part of the pipeline.
@param tree The node of the pipeline tree for the right command.
@param pfds The pipe file descriptors.
@return The child's PID or an error code.
*/
static int	ft_exec_right_child(t_node *tree, int *pfds)
{
	int	pid_r;

	pid_r = fork();
	if (!pid_r)
		ft_exec_pipe_child(tree->right, pfds, TD_RIGHT);
	return (pid_r);
}

/*
@brief Executes a pipeline of commands represented by a tree structure.
@param tree The root node of the pipeline tree.
@return The exit status of the last executed command or an error code.
*/
static int	ft_exec_pipeline(t_node *tree)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_sig.sigint = 1;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(tree->left, pfds, TD_LEFT);
	else
	{
		pid_r = ft_exec_right_child(tree, pfds);
		if (pid_r > 0)
		{
			close(pfds[0]);
			close(pfds[1]);
			waitpid(pid_l, &status, 0);
			waitpid(pid_r, &status, 0);
			g_sig.sigint = 0;
			return (ft_get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

/*
@brief Executes a node (command or pipeline) from the AST.
@param tree The AST node to execute.
@param piped Indicates whether the node is part of a pipeline.
@return The status of the execution.
*/
int	ft_exec_node(t_mini *mini, bool piped)
{
	if (!mini->ast)
		return (1);
	if (mini->ast->type == N_PIPE)
		return (ft_exec_pipeline(mini->ast));
	return (ft_exec_simple_cmd(mini, piped));
}
