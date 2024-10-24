/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:50 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/24 20:42:58 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_handle_normal_str(char *str, size_t *i)
{
	size_t	start;
	char	*substr;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	substr = ft_substr(str, start, *i - start);
	if (!substr)
		g_sig.exit_s = 1;
	return (substr);
}

char	*ft_handle_squotes(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*ft_handle_dquote_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquotes(t_mini *mini, char *str, size_t *i)
{
	char	*ret;

	ret = ft_strdup("\"");
	if (!ret)
		return (g_sig.exit_s = 1, NULL);
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret = ft_strjoinf(ret, ft_handle_dollar(mini, str, i));
		else
			ret = ft_strjoinf(ret, ft_handle_dquote_str(str, i));
	}
	if (!ret)
		return (g_sig.exit_s = 1, NULL);
	(*i)++;
	return (ft_strjoinf(ret, ft_strdup("\"")));
}
