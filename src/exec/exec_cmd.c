/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:59:19 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:36:54 by rcheong          ###   ########.fr       */
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
@brief Executes the child process for a simple command.
@param mini The minishell structure.
@param node The AST node representing the command to execute.
@return Exit status of the command.
*/
int	ft_exec_child(t_mini *mini, t_node *node)
{
	t_path	path_status;
	int		tmp_status;
	int		fork_pid;

	g_sig.sigint = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = ft_check_redirection(node);
		mini->env_var = ft_env_update(&mini);
		if (tmp_status != ENO_SUCCESS)
			(ft_clean_ms(mini), exit(ENO_GENERAL));
		path_status = ft_get_path(mini, (node->expanded_args)[0]);
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
@brief Executes a simple command, handling both built-ins and external commands.
@param node The AST node representing the command to execute.
@param piped Boolean flag indicating if the command is part of a pipeline.
@param env_var The environment variables array.
@param env The linked list of environment variables.
@return Exit status of the command.
*/
int	ft_exec_simple_cmd(t_mini *mini, t_node *node, bool piped)
{
	int		tmp_status;
	t_path	path;

	if (!node->expanded_args)
	{
		tmp_status = ft_check_redirection(node);
		return (ft_reset_stds(mini, piped), (tmp_status && ENO_GENERAL));
	}
	if (ft_isbuiltin((node->expanded_args)[0]))
	{
		tmp_status = ft_check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			return (ft_reset_stds(mini, piped), ENO_GENERAL);
		tmp_status = ft_run_builtin(mini, node->expanded_args);
		return (ft_reset_stds(mini, piped), tmp_status);
	}
	path = ft_get_path(mini, (node->expanded_args)[0]);
	if (path.err.no != ENO_SUCCESS)
	{
		ft_reset_stds(mini, piped);
		return (ft_err_msg(path.err));
	}
	return (ft_exec_child(mini, node));
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
// int	ft_exec_simple_cmd(t_mini *mini, t_node *node, bool piped)
// {
// 	int	tmp_status;

// 	if (!node->expanded_args)
// 	{
// 		tmp_status = ft_check_redirection(node);
// 		return (ft_reset_stds(mini, piped), (tmp_status && ENO_GENERAL));
// 	}
// 	else if (ft_isbuiltin((node->expanded_args)[0]))
// 	{
// 		tmp_status = ft_check_redirection(node);
// 		if (tmp_status != ENO_SUCCESS)
// 			return (ft_reset_stds(mini, piped), ENO_GENERAL);
// 		tmp_status = ft_run_builtin(node->expanded_args, mini);
// 		return (ft_reset_stds(mini, piped), tmp_status);
// 	}
// 	else if (ft_check_path(mini) == 1)
// 		return (printf("%s", "command not found\n"), -1);
			// need to fix this to print the correct error message
// 	else
// 		return (ft_exec_child(node, mini, piped));
// }
