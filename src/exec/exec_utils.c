/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:23 by chtan             #+#    #+#             */
/*   Updated: 2024/10/26 13:19:35 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
@brief Checks if a string matches a delimiter pattern.
@param delimiter The delimiter string.
@param str The string to check.
@return True if str matches the delimiter, false otherwise.
*/
bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}
