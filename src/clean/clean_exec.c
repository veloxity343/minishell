/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:44 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/06 18:23:30 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del(void *ptr)
{
	free(ptr);
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list = NULL;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		if (ptr)
			ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}
