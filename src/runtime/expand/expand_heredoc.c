/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:22:29 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 11:20:12 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_heredoc_expand_writer
// (t_mini *mini, char *str, size_t i, int fd)
// {
// 	size_t	start;
// 	char	*tmp;

// 	start = ++i;
// 	if (str[i] == '?')
// 	{
// 		ft_putnbr_fd(g_sig.exit_s, fd);
// 		return (2);
// 	}
// 	while (str[i] && str[i] != '$' && str[i] != ' ')
// 		i++;
// 	if (i != start)
// 	{
// 		tmp = ft_garbage_collector(ft_substr(str, start, i - start), false);
// 		char *env_val = ft_get_env_val(mini, tmp);
// 		free(tmp);
// 		if (env_val)
// 			{
// 				ft_putstr_fd(env_val, fd);
// 				free(env_val);
// 			}
// 	}
// 	return (i);
// }

// void	ft_heredoc_expander(t_mini *mini, char *str, int fd)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!str)
// 		return ;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			i += ft_heredoc_expand_writer(mini, str, i, fd);
// 		else
// 			i += (ft_putchar_fd(str[i], fd), 1);
// 	}
// 	ft_putchar_fd('\n', fd);
// }

static int	ft_heredoc_expand_writer(t_mini *mini, char *str, size_t i, int fd)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(g_sig.exit_s, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = ft_garbage_collector(ft_substr(str, start, i - start), false);
		tmp = ft_get_env_val(mini, tmp);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i - start + 1);
}

void	ft_heredoc_expander(t_mini *mini, char *str, int fd)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] == '$')
				i += ft_heredoc_expand_writer(mini, str, i, fd);
			else
			{
				ft_putchar_fd(str[i], fd);
				i++;
			}
		}
	}
	ft_putchar_fd('\n', fd);
}
