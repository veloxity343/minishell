/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:00 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:11:09 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Sets up the IO list for each node.
@param mini The minishell structure containing the current state.
@param io_list Linked list of IO nodes associated with this node.
@return True if successful, false otherwise.
*/
bool	ft_get_io_list(t_mini *mini, t_io_node **io_list)
{
	t_token_type	redir_type;
	t_io_node		*tmp_io_node;

	if (mini->parse_err.type)
		return (false);
	while (mini->curr_token && ft_is_redir(mini->curr_token->type))
	{
		redir_type = mini->curr_token->type;
		ft_get_next_token(mini);
		if (!mini->curr_token)
			return (ft_set_parse_err(mini, E_SYNTAX), false);
		if (mini->curr_token->type != T_IDENTIFIER)
			return (ft_set_parse_err(mini, E_SYNTAX), false);
		tmp_io_node = ft_new_io_node(redir_type, mini->curr_token->value);
		if (!tmp_io_node)
			return (ft_set_parse_err(mini, E_MEM), false);
		ft_append_io_node(io_list, tmp_io_node);
		ft_get_next_token(mini);
	}
	return (true);
}

/*
@brief Joins arguments into a single string.
@param mini The minishell structure containing the current state.
@param args The arguments as a single string.
@return True if successful, false otherwise.
*/
bool	ft_join_args(t_mini *mini, char **args)
{
	char	*to_free;

	if (mini->parse_err.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (mini->curr_token && mini->curr_token->type == T_IDENTIFIER)
	{
		to_free = *args;
		*args = ft_strjoin_char(*args, mini->curr_token->value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		ft_get_next_token(mini);
	}
	return (true);
}

/*
@brief Determines if the current token is a simple command.
@param mini The minishell structure containing the current state.
@return The node representing the simple command.
*/
t_node	*ft_get_simple_cmd(t_mini *mini)
{
	t_node	*node;

	if (mini->parse_err.type)
		return (NULL);
	node = ft_new_node(N_CMD);
	if (!node)
		return (ft_set_parse_err(mini, E_MEM), NULL);
	while (mini->curr_token && (mini->curr_token->type == T_IDENTIFIER
			|| ft_is_redir(mini->curr_token->type)))
	{
		if (mini->curr_token->type == T_IDENTIFIER)
		{
			if (!ft_join_args(mini, &(node->args)))
				return (ft_clear_cmd_node(node), ft_set_parse_err(mini, E_MEM),
					NULL);
		}
		else if (ft_is_redir(mini->curr_token->type))
		{
			if (!ft_get_io_list(mini, &(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
