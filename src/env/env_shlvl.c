/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:30:24 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/05 10:04:03 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int invalid_lvl(const char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_shlvl(t_mini *mini)
{
	char	*shlvl_value;
	int		shlvl;

	shlvl_value = ft_get_env_val(mini, "SHLVL");
	if (shlvl_value == NULL || invalid_lvl(shlvl_value))
		return (1);
	shlvl = ft_atoi(shlvl_value);
	return (shlvl >= 0 ? shlvl + 1 : 1);
}

void update_shlvl(t_mini *mini)
{
	int		new_shlvl;
	char	*new_shlvl_str;

	new_shlvl = get_shlvl(mini);
	new_shlvl_str = ft_itoa(new_shlvl);  // Convert the SHLVL integer to a string
	if (!new_shlvl_str)
		return ;  // Handle allocation failure if needed

	ft_update_env(mini, "SHLVL", new_shlvl_str, true);
	ft_garbage_collector(new_shlvl_str, false);  // Collect memory if needed
}
