/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:00:01 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 11:31:12 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Checks if a given environment key exists in the environment list.
@param mini A pointer to the minishell structure containing the environment list.
@param key The key to search for.
@return true if the key exists, false otherwise.
*/
bool	ft_env_entry_exists(t_mini *mini, char *key)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (true);
		env = env->next;
	}
	return (false);
}

/*
@brief Creates a new environment list node.
@param key The key for the new environment entry.
@param value The value for the new environment entry.
@return A pointer to the newly created environment node.
*/
static t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

/*
@brief Retrieves the value of a given environment variable from the list.
@param mini A pointer to the minishell structure containing the environment list.
@param key The key to search for.
@return The value associated with the key, or NULL if not found.
*/
char	*ft_get_env_val(t_mini *mini, char *key)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
@brief Appends a new node to the end of the environment list.
@param mini A pointer to the minishell structure containing the environment list.
@param new The new environment node to append.
@return None.
*/
static void	ft_env_back(t_mini *mini, t_env *new)
{
	t_env	*curr;

	if (!mini->env)
	{
		mini->env = new;
		return ;
	}
	curr = mini->env;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

/*
@brief Updates an existing environment variable
    or creates a new one if not found.
@param mini A pointer to the minishell structure containing the environment list.
@param key The key of the environment variable.
@param value The value of the environment variable.
@param create Whether to create the variable if it doesn't exist.
@return None.
*/
void	ft_update_env(t_mini *mini, char *key, char *value, bool create)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			if (value)
				env->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		env = env->next;
	}
	if (create)
		ft_env_back(mini, ft_env_new(key, value));
}
