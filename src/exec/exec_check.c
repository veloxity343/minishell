/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:59:46 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:59:47 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Checks if a file is executable.
@param file The file path to check.
@param cmd Indicates if the check is for a command.
@return A t_err structure containing error status and message.
*/
t_err	ft_check_exec(char *file, bool cmd)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ENO_CANT_EXEC, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	if (cmd)
		return ((t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, file});
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

/*
@brief Checks if a file is readable.
@param file The file path to check.
@return A t_err structure containing error status and message.
*/
t_err	ft_check_read(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

/*
@brief Checks if a file is writable.
@param file The file path to check.
@return A t_err structure containing error status and message.
*/
t_err	ft_check_write(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}
