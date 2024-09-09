/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:35:19 by chtan             #+#    #+#             */
/*   Updated: 2024/09/08 20:57:26 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/temp.h"
#include "../inc/define_lib.h"

void	error_msg(char *msg)
{
	ft_printf("\033[31mError\033[0m");
	ft_dprintf(2, ": %s\n", msg);
	exit_sig(2);
}