/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:27:59 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/03 16:38:45 by chtan            ###   ########.fr       */
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

static void	ft_export_list(t_mini *mini)
{
	t_env	*list;
	size_t	i;

	list = mini->env;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			ft_printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					ft_printf("\\%c", (list->value)[i++]);
				else
					ft_printf("%c", (list->value)[i++]);
			}
			ft_printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			ft_printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

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
	mini->env_var = env_update(&mini);
	return (g_sig.exit_s);
}
