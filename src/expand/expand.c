/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:26 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/22 11:31:00 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_empty_strs(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*ret;
	size_t	dstsize;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"'
			&& str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '"' && str[i
					+ 1] == '"'))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	dstsize = ft_strlen(tmp) + 1;
	ret = ft_calloc(dstsize, sizeof(char));
	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
}

char	*ft_handle_dollar(t_mini *mini, char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(mini->exit_s));
	}
	else if (!ft_is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (ft_is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = ft_get_env_val(mini, var);
	if (!env_val)
		return (free(var), mini->exit_s = 1, ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

static char	*ft_cmd_pre_expander(t_mini *mini, char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoinf(ret, ft_handle_squotes(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoinf(ret, ft_handle_dquotes(mini, str, &i));
		else if (str[i] == '$')
			ret = ft_strjoinf(ret, ft_handle_dollar(mini, str, &i));
		else
			ret = ft_strjoinf(ret, ft_handle_normal_str(str, &i));
		if (!ret)
			return (mini->exit_s = 1, NULL);
	}
	return (ret);
}

char	**ft_expand(t_mini *mini, char *str)
{
	char	**expanded;
	size_t	i;

	str = ft_cmd_pre_expander(mini, str);
	if (!str)
		return (mini->exit_s = 1, NULL);
	str = ft_clean_empty_strs(str);
	if (!str)
		return (mini->exit_s = 1, NULL);
	expanded = ft_expander_split(str);
	free(str);
	if (!expanded)
		return (mini->exit_s = 1, NULL);
	i = 0;
	while (expanded[i])
	{
		expanded[i] = ft_strip_quotes(expanded[i]);
		i++;
	}
	return (expanded);
}
