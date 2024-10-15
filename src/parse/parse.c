/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:49 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/15 21:48:15 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_combine(t_mini *mini, t_token_type op, t_node *left, t_node *right)
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
	if (ft_curr_token_is_binop(mini) || mini->curr_token->type == T_C_PAREN)
		return (ft_set_parse_err(mini, E_SYNTAX), NULL);
	else if (mini->curr_token->type == T_O_PAREN)
	{
		ft_get_next_token(mini);
		node = ft_expression(mini, 0);
		if (!node)
			return (ft_set_parse_err(mini, E_MEM), NULL);
		if (!mini->curr_token || mini->curr_token->type != T_C_PAREN)
			return (ft_set_parse_err(mini, E_SYNTAX), node);
		ft_get_next_token(mini);
		return (node);
	}
	else
		return (ft_get_simple_cmd(mini));
}

t_node	*ft_expression(t_mini *mini, int min_prec)
{
	t_node			*left;
	t_node			*right;
	t_token_type	op;

	if (mini->parse_err.type || !mini->curr_token)
		return (NULL);
	left = ft_term(mini);
	if (!left)
		return (NULL);
	while (ft_curr_token_is_binop(mini))
	{
		op = mini->curr_token->type;
		ft_get_next_token(mini);
		if (!mini->curr_token)
			return (ft_set_parse_err(mini, E_SYNTAX), left);
		right = ft_expression(mini, 1);
		if (!right)
			return (left);
		left = ft_combine(mini, op, left, right);
		if (!left)
			return (ft_clear_ast(mini, &left), ft_clear_ast(mini, &right),
				NULL);
	}
	return (left);
}

t_node	*ft_parse(t_mini *mini)
{
	t_node	*ast;

	mini->curr_token = mini->tokens;
	ast = ft_expression(mini, 0);
	if (mini->curr_token)
		return (ft_set_parse_err(mini, E_SYNTAX), ast);
	return (ast);
}
