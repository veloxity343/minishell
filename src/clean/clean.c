/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:40 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:46:41 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
