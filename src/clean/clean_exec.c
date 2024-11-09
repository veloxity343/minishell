/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:44 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 11:17:41 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

// void	*ft_garbage_collector(void *ptr, bool clean)
// {
// 	static t_list	*garbage_list;

// 	if (clean)
// 	{
// 		ft_lstclear(&garbage_list, ft_del);
// 		return (NULL);
// 	}
// 	else
// 	{
// 		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
// 		return (ptr);
// 	}
// }

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
