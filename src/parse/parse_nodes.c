/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:55 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:09:11 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Gets the IO type from the token type.
@param type The token type.
@return The IO type.
*/
t_io_type	ft_get_io_type(t_token_type type)
{
	if (type == T_IN_REDIR)
		return (IO_IN);
	if (type == T_OUT_REDIR)
		return (IO_OUT);
	if (type == T_HEREDOC)
		return (IO_HEREDOC);
	return (IO_APPEND);
}

/*
@brief Creates a new node.
@param type The type of node.
@return The new node.
*/
t_node	*ft_new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

/*
@brief Creates a new IO node.
@param type The type of IO node.
@param value The value of the IO node.
@return The new IO node.
*/
t_io_node	*ft_new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_node;

	new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = ft_get_io_type(type);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

/*
@brief Appends a new IO node to the end of the list.
@param lst The list to append to.
@param new The new node to append.
@return None.
*/
void	ft_append_io_node(t_io_node **lst, t_io_node *new)
{
	t_io_node	*curr_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new;
}
