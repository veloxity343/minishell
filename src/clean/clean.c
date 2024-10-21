/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:40 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 17:26:40 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_char2(char **tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}

void	ft_free_char3(char ***tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		ft_free_char2(tofree[i++]);
	free(tofree);
}

static void	ft_clear_env(t_env **env)
{
	t_env	*env_tofree;

	while (*env)
	{
		env_tofree = *env;
		*env = (*env)->next;
		free(env_tofree);
	}
	*env = NULL;
}

void	ft_clean_ms(t_mini *mini)
{
	ft_garbage_collector(NULL, true);
	ft_clear_ast(mini, &mini->ast);
	ft_clear_env(&mini->env);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->ori_term);
}
