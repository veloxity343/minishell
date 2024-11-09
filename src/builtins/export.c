/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:47:26 by chtan             #+#    #+#             */
/*   Updated: 2024/11/09 11:31:38 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("trash: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	ft_count_env_entries(char **env_array)
{
	int	count;

	count = 0;
	while (env_array[count])
		count++;
	return (count);
}

/*
@brief Sorts and prints the environment variables if
	no arguments are provided.
@param mini The minishell structure.
*/
static void	ft_export_list(t_mini *mini)
{
	char	**env_array;
	int		env_len;

	env_array = mini->env_var;
	env_len = ft_count_env_entries(env_array);
	if (!env_array)
		return ;
	ft_sort_env(env_array, env_len);
	ft_print_sorted_env(env_array);
}

/*
@brief Ensures that the key is a valid identifier.
@param str The string to check.
@return 1 if the key is valid, 0 otherwise.
*/
int	ft_check_key(const char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
@brief Implements the export command, with or without arguments.
@param mini The minishell structure.
@param argv The arguments to the export command.
@return The exit status of the export command.
*/
int	ft_export(t_mini *mini, char **argv)
{
	int		i;
	char	*key;

	i = 1;
	g_sig.exit_s = 0;
	if (!argv[1])
		return (ft_export_list(mini), 0);
	while (argv[i])
	{
		if (ft_check_key(argv[i]) == 0)
			g_sig.exit_s = ft_export_err_msg(argv[i]);
		else
		{
			key = ft_extract_key(argv[i]);
			if (ft_env_entry_exists(mini, key))
				ft_update_env(mini, key, ft_extract_value(argv[i]), false);
			else
				ft_update_env(mini, key, ft_extract_value(argv[i]), true);
		}
		i++;
	}
	return (g_sig.exit_s);
}
