/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:08 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:42:44 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Returns the size of the environment variable name.
@details This function iterates through the provided environment variable string
until it encounters an '=' character,
	counting the number of characters before it.
This helps determine the length of the variable name.
@param env The environment variable string.
@return The size of the variable name, excluding the '=' character.
*/
static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

/*
@brief Frees the memory allocated for a given environment variable node.
@details This function checks if the node to be freed is the 
	only node in the list and handles the cleanup accordingly.
	If it is not the only node, it frees the value
and the node itself.
@param mini A pointer to the minishell structure containing the environment.
@param env A pointer to the environment variable node to be freed.
*/
static void	free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		env->value = NULL;
		env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

/*
@brief Removes an environment variable from the minishell environment.
@details This function searches for the environment variable specified in the
arguments and removes it from the linked list of environment variables.
If the variable is found at the head of the list, it updates the head pointer.
@param args The array of command-line arguments where args[1]
	is the variable to unset.
@param mini A pointer to the minishell structure containing the environment.
@return Returns 0 upon successful completion, or a negative value on failure.
*/
int	ft_unset(char **args, t_mini *mini)
{
	t_env	*current;

	current = mini->env;
	if (!args[1])
		return (0);
	if (ft_strncmp(args[1], current->value, env_size(current->value)) == 0)
	{
		mini->env = current->next;
		free_node(mini, current);
		return (0);
	}
	while (current && current->next)
	{
		if (ft_strncmp(args[1], current->next->value,
				env_size(current->next->value)) == 0)
		{
			free_node(mini, current->next);
			current->next = current->next->next;
			return (0);
		}
		current = current->next;
	}
	return (0);
}
