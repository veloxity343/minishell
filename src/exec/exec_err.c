/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:18:55 by chtan             #+#    #+#             */
/*   Updated: 2024/10/26 13:18:57 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err_msg(t_err err)
{
	if (err.msg == ERRMSG_CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": command not found\n", 2), err.no);
	else if (err.msg == ERRMSG_NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": No such file or directory\n", 2), err.no);
	else if (err.msg == ERRMSG_PERM_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": Permission denied\n", 2), err.no);
	else if (err.msg == ERRMSG_AMBIGUOUS)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), err.no);
	else if (err.msg == ERRMSG_TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			err.no);
	else if (err.msg == ERRMSG_NUMERIC_REQUI)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(err.cause, 2),
			ft_putstr_fd(": numeric argument required\n", 2), err.no);
	return (0);
}
