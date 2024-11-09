/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:44 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 11:33:30 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/*
@brief Stores a pointer in a linked list for garbage day.
@param ptr The pointer to store.
@param clean If true, clears the linked list, stores otherwise.
*/
void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;
	t_list			*new_node;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		new_node = ft_lstnew(ptr);
		if (!new_node)
		{
			free(ptr);
			return (NULL);
		}
		ft_lstadd_back(&garbage_list, new_node);
		return (ptr);
	}
}
