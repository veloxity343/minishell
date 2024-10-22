/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:01 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/22 11:02:23 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Executes the child process for pipes, handling left and right dirs.
@param mini The shell context (contains environment, AST, etc.).
@param pfds The pipe file descriptors.
@param dir The direction of the pipe (TD_LEFT or TD_RIGHT).
*/
static void	ft_exec_pipe_child(t_mini *mini, int pfds[2], t_ast_dir dir)
{
	int	status;

	status = 0;
	if (dir == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
		status = ft_exec_node(mini, true);
	}
	else if (dir == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
		status = ft_exec_node(mini, true);
	}
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
@brief Forks a child process to execute a command in the right part of the pipeline.
@param mini The shell context (contains environment, AST, etc.).
@param pfds The pipe file descriptors.
@return The child's PID or an error code.
*/
static int	ft_exec_right_child(t_mini *mini, int *pfds)
{
	int	pid_r;

	pid_r = fork();
	if (!pid_r)
		ft_exec_pipe_child(mini, pfds, TD_RIGHT);
	return (pid_r);
}

/*
@brief Executes a pipeline of commands represented by a tree structure.
@param mini The shell context (contains environment, AST, etc.).
@return The exit status of the last executed command or an error code.
*/
static int	ft_exec_pipeline(t_mini *mini)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_sig.sigint = 1;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(mini, pfds, TD_LEFT);
	else
	{
		pid_r = ft_exec_right_child(mini, pfds);
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
@param mini The shell context (contains environment, AST, etc.).
@param piped Indicates whether the node is part of a pipeline.
@return The status of the execution.
*/
int	ft_exec_node(t_mini *mini, bool piped)
{
	if (!mini->ast)
		return (1);
	if (mini->ast->type == N_PIPE)
		return (ft_exec_pipeline(mini));
	return (ft_exec_simple_cmd(mini, piped));
}
