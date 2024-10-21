/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:49 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 18:05:15 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_combine(t_mini *mini, t_node *left, t_node *right)
{
	t_node	*node;

	if (mini->parse_err.type)
		return (NULL);
	node = ft_new_node(N_PIPE);
	if (!node)
		return (ft_set_parse_err(mini, E_MEM), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*ft_term(t_mini *mini)
{
	t_node	*node;

	if (mini->parse_err.type)
		return (NULL);
	if (ft_curr_token_is_binop(mini))
		return (ft_set_parse_err(mini, E_SYNTAX), NULL);
	node = ft_get_simple_cmd(mini);
	if (!node)
		return (ft_set_parse_err(mini, E_MEM), NULL);
	return (node);
}

t_node	*ft_expression(t_mini *mini)
{
	t_node	*left;
	t_node	*right;

	if (mini->parse_err.type || !mini->curr_token)
		return (NULL);
	left = ft_term(mini);
	if (!left)
		return (NULL);
	while (ft_curr_token_is_binop(mini))
	{
		ft_get_next_token(mini);
		if (!mini->curr_token)
			return (ft_set_parse_err(mini, E_SYNTAX), left);
		right = ft_expression(mini);
		if (!right)
			return (left);
		left = ft_combine(mini, left, right);
		if (!left)
			return (ft_clear_ast(mini, &left), ft_clear_ast(mini, &right),
				NULL);
	}
	return (left);
}

t_node	*ft_parser(t_mini *mini)
{
	t_node	*ast;

	mini->curr_token = mini->tokens;
	ast = ft_expression(mini);
	if (mini->curr_token)
		return (ft_set_parse_err(mini, E_SYNTAX), ast);
	return (ast);
}
