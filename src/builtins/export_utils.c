/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:47:38 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:45:48 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Prints the sorted environment array with
	the format "declare -x key=value".
@param env_array The environment array to print.
*/
void	ft_print_sorted_env(char **env_array)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env_array[i])
	{
		key = ft_extract_key(env_array[i]);
		value = ft_extract_value(env_array[i]);
		if (value)
			ft_printf("declare -x %s=\"%s\"\n", key, value);
		else
			ft_printf("declare -x %s\n", key);
		i++;
	}
}

/*
@brief Bubble sorts the environment array.
@param tab The environment array to sort.
@param env_len The length of the environment array.
*/
void	ft_sort_env(char **tab, int env_len)
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

/* static int	ft_count_env_entries(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

static void	ft_add_env_entries_to_array(t_env *env, char **env_array)
{
	int		i;
	char	*entry;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			entry = ft_strjoin(ft_strjoin(env->key, "="), env->value);
			if (entry)
				env_array[i++] = entry;
		}
		env = env->next;
	}
	env_array[i] = NULL;
}

char	**ft_convert_env_to_array(t_env *env, int *env_len)
{
	char	**env_array;

	*env_len = ft_count_env_entries(env);
	env_array = malloc(sizeof(char *) * (*env_len + 1));
	if (!env_array)
		return (NULL);
	ft_add_env_entries_to_array(env, env_array);
	return (env_array);
} */
