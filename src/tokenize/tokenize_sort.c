/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:24 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:17:10 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Creates a new token and initializes it.
@param lst The linked list of tokens.
@return None.
*/
t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

/*
@brief Adds a new token to the end of the token list.
@param lst The linked list of tokens.
@param new_token The new token to add.
@return None.
*/
void	ft_token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node -> next)
		curr_node = curr_node -> next;
	curr_node -> next = new_token;
	new_token -> prev = curr_node;
}
