/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:06:37 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/19 15:06:51 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief General function for opening a file for input, output, or appending.
@param path The file path to open.
@param flags The flags to use for opening the file (e.g., O_RDONLY, O_WRONLY).
@param mode The mode to use when creating the file (e.g., 0644).
@param status Pointer to the status code for error reporting.
@return The file descriptor on success, or -1 on failure.
*/
int	ft_open_file(char *path, int flags, int mode, int *status)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(path));
		return (-1);
	}
	return (fd);
}

/*
@brief Handles output redirection (i.e., '>') by opening/creating a file.
@param io_list The I/O node containing file redirection information.
@param status Pointer to the status code for error reporting.
@return The status code (0 for success, non-zero for failure).
*/
int	ft_out(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_list->value});
		return (*status);
	}
	fd = ft_open_file(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC,
			0644, status);
	if (fd == -1)
		return (*status);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}

/*
@brief Handles input redirection (i.e., '<') by opening a file for reading.
@param io_list The I/O node containing file redirection information.
@param status Pointer to the status code for error reporting.
@return The status code (0 for success, non-zero for failure).
*/
int	ft_in(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_list->value});
		return (*status);
	}
	fd = ft_open_file(io_list->expanded_value[0], O_RDONLY, 0, status);
	if (fd == -1)
		return (*status);
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (0);
}

/*
@brief Handles append redirection (i.e.,
	'>>') by opening/creating a file in append mode.
@param io_list The I/O node containing file redirection information.
@param status Pointer to the status code for error reporting.
@return The status code (0 for success, non-zero for failure).
*/
int	ft_append(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS,
				io_list->value});
		return (*status);
	}
	fd = ft_open_file(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND,
			0644, status);
	if (fd == -1)
		return (*status);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
