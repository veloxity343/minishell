/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:53 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:07:37 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Sets current token as the next token in the list.
@param mini The minishell structure containing the current state.
@return None.
*/
void	ft_get_next_token(t_mini *mini)
{
	mini->curr_token = mini->curr_token->next;
}

/*
@brief Checks if the current token is a binary operator.
@param mini The minishell structure containing the current state.
@return True if the current token is a binary operator, false otherwise.
*/
bool	ft_curr_token_is_binop(t_mini *mini)
{
	t_token_type	type;

	if (!mini->curr_token)
		return (false);
	type = mini->curr_token->type;
	if (type == T_PIPE)
		return (true);
	return (false);
}

/*
@brief Checks if the token type is a redirection.
@param type Token type.
@return True if the token is a redirection, false otherwise.
*/
bool	ft_is_redir(t_token_type type)
{
	if (type == T_IN_REDIR || type == T_OUT_REDIR || type == T_HEREDOC
		|| type == T_APPEND)
		return (true);
	return (false);
}
