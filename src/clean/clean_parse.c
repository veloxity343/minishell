/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:05 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:39:48 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Clears the token list.
@param lst The token list to clear.
*/
void	ft_clear_token_list(t_token **lst)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *lst;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

/*
@brief Clears the I/O list.
@param lst The I/O list to clear.
*/
void	ft_clear_io_list(t_io_node **lst)
{
	t_io_node	*curr_node;
	t_io_node	*next;

	curr_node = *lst;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		ft_free_char2(curr_node->expanded_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

void	ft_clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	ft_clear_io_list(&(node->io_list));
	free(node->args);
	ft_free_char2(node->expanded_args);
}

/*
@brief Recursively clears the AST.
@param mini The minishell structure.
@param node The node to clear.
@details Clears the command node and recursively clears
	the left and right nodes.
*/
void	ft_recursive_clear_ast(t_mini *mini, t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_CMD)
		ft_clear_cmd_node(node);
	else
	{
		if (node->left)
			ft_recursive_clear_ast(mini, node->left);
		if (node->right)
			ft_recursive_clear_ast(mini, node->right);
	}
	free(node);
}

/*
@brief Clears the AST and token list.
@param mini The minishell structure.
@param ast The AST to clear.
*/
void	ft_clear_ast(t_mini *mini, t_node **ast)
{
	ft_recursive_clear_ast(mini, *ast);
	*ast = NULL;
	ft_clear_token_list(&mini->tokens);
}
