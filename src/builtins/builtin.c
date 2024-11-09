/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:40 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:41:37 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Checks if the argument is a built-in command.
@param arg The argument to check.
@return True if the argument is a built-in command, false otherwise.
*/
bool	ft_isbuiltin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}

/*
@brief Executes the built-in command.
@param mini The minishell structure.
@param args The arguments to the built-in command.
@return The exit status of the built-in command.
*/
int	ft_run_builtin(t_mini *mini, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(mini, args[1]));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(mini));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(mini, args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(mini, args));
	ft_exit(mini, args);
	return (1);
}
