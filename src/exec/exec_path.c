/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:48:46 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/22 11:11:36 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Finds the full path to the command based on the PATH environment variable.
@param path The PATH environment variable value.
@param cmd The command to search for.
@return A t_path structure containing the error and command path.
*/
static t_path	ft_get_env_path(char *path, char *cmd)
{
	size_t	i;
	t_err	err;
	char	*cmd_path;
	char	**split_path;

	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		cmd_path = ft_garbage_collector(ft_strjoin_char(
					ft_strdup(split_path[i]), ft_strdup(cmd), '/'), false);
		err = ft_check_exec(cmd_path, true);
		if (err.no == ENO_SUCCESS)
			return ((t_path){(t_err){ENO_SUCCESS, 42, cmd_path}, cmd_path});
		i++;
	}
	ft_free_char2(split_path);
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
}

/*
@brief Retrieves the full path of the command,
	checking both absolute paths and PATH env variable.
@param cmd The command to search for.
@param env The environment variable list.
@return A t_path structure containing the error and the command path.
*/
t_path	ft_get_path(char *cmd, t_mini *mini)
{
	char	*value;

	if (*cmd == '\0')
		return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd},
			NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){ft_check_exec(cmd, false), cmd});
	value = ft_get_env_val(mini, "PATH");
	if (value)
		return (ft_get_env_path(value, cmd));
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, cmd}, NULL});
}
