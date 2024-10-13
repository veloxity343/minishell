/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_level.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:50:36 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/13 14:55:41 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_lvl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_spacenl(str, &i);
	if (invalid_lvl(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	increment_shell_level(t_env *env)
{
	int		new_lvl;
	char	env_name[BUFFER_SIZE];
	char	*shlvl;
	char	*sh_lvl_val;

	sh_lvl_val = get_env_value("SH_LVL", env);
	if (ft_strcmp(sh_lvl_val, "") == 0)
		return ;
	new_lvl = get_lvl(sh_lvl_val) + 1;
	ft_memdel(sh_lvl_val);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp("SH_LVL", env_name) == 0)
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(new_lvl);
			env->value = ft_strjoin("SH_LVL=", shlvl);
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}
