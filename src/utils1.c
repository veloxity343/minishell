/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:35:19 by chtan             #+#    #+#             */
/*   Updated: 2024/09/06 19:49:08 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_msg(char *msg)
{
	ft_printf("\033[31mError\033[0m");
	ft_dprintf(2, ": %s\n", msg);
	exit_sig(2);
}