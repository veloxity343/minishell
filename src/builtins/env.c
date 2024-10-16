/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:27:46 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:27:47 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Prints all environment variables to the standard output.
@param env A pointer to the environment linked list.
@details This function iterates through the environment variable linked list and
prints each variable's value to the standard output, one per line.
@return Always returns 0.
*/
int	ft_print_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (0);
}
