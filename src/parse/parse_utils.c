/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:53 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/15 22:08:35 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_next_token(t_mini *mini)
{
	mini->curr_token = mini->curr_token->next;
}

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

bool	ft_is_redir(t_token_type type)
{
	if (type == T_IN_REDIR || type == T_OUT_REDIR || type == T_HEREDOC
		|| type == T_APPEND)
		return (true);
	return (false);
}
