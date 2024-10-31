/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:47:08 by chtan             #+#    #+#             */
/*   Updated: 2024/10/31 17:54:49 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Extracts the key from a string in the format 'key=value'.
@param str The input string containing the key-value pair.
@return A newly allocated string containing the key.
*/
char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

/*
@brief Extracts the value from a string in the format 'key=value'.
@param str The input string containing the key-value pair.
@return A newly allocated string containing the value,
	or NULL if no value exists.
*/
char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_collector(ft_substr(str, i, ft_strlen(str) - i),
					false));
		}
		i++;
	}
	return (NULL);
}

/*
@brief Initializes the environment list based on the system environment.
@param mini A pointer to the minishell structure containing the environment list.
@return None.
*/
void	ft_init_env(t_mini *mini)
{
	int		i;
	char	**env_var;
	char	*key;
	char	*value;

	env_var = mini->env_var;
	if (!env_var)
		return ;
	i = 0;
	while (env_var[i])
	{
		key = ft_extract_key(env_var[i]);
		value = ft_extract_value(env_var[i]);
		ft_update_env(mini, key, value, true);
		i++;
	}
}

/*
@brief Prints all environment variables in the environment list.
@param mini A pointer to the minishell structure containing the environment list.
@return ENO_SUCCESS on success.
*/
int	ft_env(t_mini *mini)
{
	t_env	*list;

	list = mini->env;
	while (list)
	{
		if (list->value != NULL)
			ft_printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}

/*
@brief Initializes the SHLVL environment variable.
*/
void	initialize_shlvl(t_mini *mini)
{
	int		level;
	char	*shlvl;
	char	*export_str;
	char	*args[3];

	level = 0;
	shlvl = ft_get_env_val(mini, "SHLVL");
	level = ft_atoi(shlvl);
	level++;
	free(shlvl);
	shlvl = ft_itoa(level);
	export_str = malloc(strlen("SHLVL=") + strlen(shlvl) + 1);
	ft_strcpy(export_str, "SHLVL=");
	ft_strcat(export_str, shlvl);
	args[0] = "export";
	args[1] = ft_strdup(export_str);
	args[2] = NULL;
	ft_export(mini, args);
	free(shlvl);
	free(export_str);
	free(args[1]);
}
