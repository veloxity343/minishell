/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:59:19 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/31 16:03:41 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Handles I/O redirections for the command node.
@param node The AST node containing I/O redirection information.
@return ENO_SUCCESS on success, or an error code on failure.
*/
int	ft_check_redirection(t_node *node)
{
	t_io_node	*tmp_io;
	int			tmp_status;

	tmp_io = node->io_list;
	while (tmp_io)
	{
		if (tmp_io->type == IO_OUT && ft_out(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_IN && ft_in(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_APPEND && ft_append(tmp_io,
				&tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_HEREDOC)
			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

/*
@brief Resets stdin and stdout to their original file descriptors if not piped.
@param piped Boolean flag indicating if the command is piped.
*/
void	ft_reset_stds(t_mini *mini, bool piped)
{
	if (piped)
		return ;
	dup2(mini->stdin, 0);
	dup2(mini->stdout, 1);
}

/*
@brief Executes a command in a child process.
@param node The AST node representing the command to execute.
@param env_var The environment variables array.
@param env The linked list of environment variables.
@return Exit status of the command.
*/
static int	ft_exec_child(t_node *node, t_mini *mini)
{
	t_path	path_status;
	int		tmp_status;
	int		fork_pid;

	g_sig.sigint = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = ft_check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			(ft_clean_ms(mini), exit(ENO_GENERAL));
		path_status = ft_get_path((node->expanded_args)[0], mini);
		if (path_status.err.no != ENO_SUCCESS)
		{
			tmp_status = ft_err_msg(path_status.err);
			(ft_clean_ms(mini), exit(tmp_status));
		}
		if (execve(path_status.path, node->expanded_args, mini->env_var) == -1)
			(ft_clean_ms(mini), exit(1));
	}
	waitpid(fork_pid, &tmp_status, 0);
	g_sig.sigint = false;
	return (ft_get_exit_status(tmp_status));
}

/*
	check if the path is set in the environment
	before executing the command
*/
// static int	ft_check_path(t_mini *mini)
// {
// 	const char	*check = "PATH";
// 	t_env		*env;

// 	env = mini->env;
// 	while (env)
// 	{
// 		if (ft_strncmp(env->key, check, 4) == 0)
// 			return (0);
// 		env = env->next;
// 	}
// 	return (1);
// }

/*
@brief Executes a simple command, handling both built-ins and external commands.
@param node The AST node representing the command to execute.
@param piped Boolean flag indicating if the command is part of a pipeline.
@param env_var The environment variables array.
@param env The linked list of environment variables.
@return Exit status of the command.
*/
int	ft_exec_simple_cmd(t_mini *mini, bool piped)
{
	int	tmp_status;

	if (!mini->ast->expanded_args)
	{
		tmp_status = ft_check_redirection(mini->ast);
		if (tmp_status)
			return (ENO_GENERAL);
		else
			return (ENO_SUCCESS);
	}
	else if (ft_isbuiltin((mini->ast->expanded_args)[0]))
	{
		tmp_status = ft_check_redirection(mini->ast);
		if (tmp_status != ENO_SUCCESS)
			return (ft_reset_stds(mini, piped), ENO_GENERAL);
		tmp_status = ft_run_builtin(mini->ast->expanded_args, mini);
		return (ft_reset_stds(mini, piped), tmp_status);
	}
	else
		return (ft_exec_child(mini->ast, mini));
}
