/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:40 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:27:16 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	run_builtin(char **args, t_mini *mini)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini->env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, mini->env, mini->muted_env);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, mini);
	return (result);
}
