/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:05:15 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/30 21:08:15 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_assignment(const char *str)
{
	int i = 0;

	// Check if there is an equal sign and valid variable name characters
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=');  // Return true if there's an '=' sign after valid key
}

int ft_handle_assignment(t_mini *mini, char *assignment)
{
	char *key;
	char *value;

	key = ft_extract_key(assignment);
	value = ft_extract_value(assignment);
	if (ft_env_entry_exists(mini, key))
		ft_update_env(mini, key, value, false);
	else
		ft_update_env(mini, key, value, true);
	free(key);
	free(value);
	return (0);
}
