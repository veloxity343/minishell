/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:08 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:47:54 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_env_var(t_mini *mini, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = mini->env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (prev)
				prev->next = current->next;
			else
				mini->env = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/*
@brief Implements 'unset', removing environment variables.
@param mini The minishell structure.
@param args The arguments to the 'unset' command.
@return 0 on success, 1 on error.
*/
int	ft_unset(t_mini *mini, char **args)
{
	int		i;
	bool	err;
	char	*key;

	i = 1;
	if (!args[1])
		return (0);
	err = false;
	while (args[i])
	{
		if (!ft_check_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
		{
			key = ft_garbage_collector(ft_extract_key(args[i]), false);
			ft_remove_env_var(mini, key);
		}
		i++;
	}
	return (err);
}
