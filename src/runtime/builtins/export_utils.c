/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:47:38 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/05 11:51:03 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

char	**convert_env_to_array(t_env *env, int *env_len)
{
	t_env	*current;
	char	**env_array;
	int		i;
	char	*entry;

	// Count the number of environment variables
	*env_len = 0;
	current = env;
	while (current)
	{
		if (current->value) // Exclude null values if necessary
			(*env_len)++;
		current = current->next;
	}

	// Allocate array of strings
	env_array = malloc(sizeof(char *) * (*env_len + 1));
	if (!env_array)
		return (NULL);

	// Copy "key=value" strings into the array
	i = 0;
	current = env;
	while (current)
	{
		if (current->value)
		{
			entry = ft_strjoin(ft_strjoin(current->key, "="), current->value);
			env_array[i++] = entry;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	print_sorted_env(char **env_array)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env_array[i])
	{
		// Split the "key=value" string
		key = ft_extract_key(env_array[i]);
		value = ft_extract_value(env_array[i]);
		
		// Print in the format "declare -x key="value""
		if (value)
			ft_printf("declare -x %s=\"%s\"\n", key, value);
		else
			ft_printf("declare -x %s\n", key);

		free(key);
		free(value);
		i++;
	}
}
