/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:20 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:28:21 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Updates the linked list of tokens by adjusting their pointers.
@details This function modifies the links between tokens in a doubly linked list
to remove a specified token and insert it in a new position,
	ensuring the integrity
of the list.
@param token A pointer to the token that is being moved.
@param prev A pointer to the token that should precede the moving token.
@param mini A pointer to the minishell structure containing the start of the token list.
*/
static void	update_token_links(t_token *token, t_token *prev, t_mini *mini)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev)
		token->next = prev->next;
	else
		token->next = mini->start;
	if (!prev)
		prev = token;
	prev->next->prev = token;
	if (mini->start->prev)
		prev->next = prev->next;
	else
		prev->next = token;
	if (mini->start->prev)
		mini->start = mini->start->prev;
	else
		mini->start = mini->start;
}

/*
@brief Merges arguments in the token list based on specific conditions.
@details This function iterates through the tokens, checks their types,
	and merges
arguments by adjusting their links if they match certain criteria. It uses helper
functions to identify previous tokens and their validity.
@param mini A pointer to the minishell structure containing the token list.
*/
void	merge_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)
	{
		prev = prev_sep(token, 0);
		if (is_type(token, ARG) && match_type(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			update_token_links(token, prev, mini);
		}
		token = token->next;
	}
}
