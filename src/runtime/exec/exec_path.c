/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:48:46 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/08 15:23:18 by rcheong          ###   ########.fr       */
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
		cmd_path = ft_garbage_collector(ft_strjoin_charf(
					ft_strdup(split_path[i]), ft_strdup(cmd), '/'), false);
		err = ft_check_exec(cmd_path, true);
		if (err.no == ENO_SUCCESS)
        {
            ft_free_char2(split_path);
			return ((t_path){(t_err){ENO_SUCCESS, 42, cmd_path}, cmd_path});
        }
        free(cmd_path);
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

char	**env_update(t_mini **mini)
{
	int		i;
	int		j;
	char	**new_env;
	t_env	*env1;
	char	*temp;

	i = 0;
	j = 0;
	env1 = (*mini)->env;
	while (env1)
	{
		i++;
		env1 = env1->next;
	}
	new_env = ft_garbage_collector(malloc(sizeof(char *) * (i + 1)), false);
	if (!new_env)
		return (NULL);
	env1 = (*mini)->env;
	while (env1)
	{
		temp = ft_garbage_collector(ft_strjoin(env1->key, "="), false);
		if (!temp)
			return (NULL);
		new_env[j] = ft_garbage_collector(ft_strjoin(temp, env1->value), false);
		if (!new_env[j])
			return (NULL);
		env1 = env1->next;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

/* char **env_update(t_mini **mini)
{
    int i;
    int j;
    char **new_env;
    t_env *env1;

	i = 0;
	j = 0;
    env1 = (*mini)->env;
    while (env1)
    {
        i++;
        env1 = env1->next;
    }
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return NULL;
    env1 = (*mini)->env;
    while (env1)
    {
        char *temp;
        temp = ft_strjoin(env1->key, "=");
        new_env[j] = ft_strjoin(temp, env1->value);
        free(temp);
        if (!new_env[j])
        {
            while (j-- > 0)
                free(new_env[j]);
            free(new_env);
            return NULL;
        }
        env1 = env1->next;
        j++;
    }
    new_env[j] = NULL;
    return new_env;
} */

// char	**env_update(t_mini **mini)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;
// 	t_env	*env1;

// 	i = 0;
// 	j = 0;
// 	env1 = (*mini)->env;
// 	while (env1)
// 	{
// 		i++;
// 		env1 = env1->next;
// 	}
// 	new_env = malloc(sizeof(char *) * (i + 1));
// 	env1 = (*mini)->env;
// 	while (i-- > 0)
// 	{
// 		new_env[j] = malloc(sizeof(char)
// 			* (ft_strlen(env1->key) + ft_strlen(env1->value) + 2));
// 		new_env[j] = ft_strjoin(env1->key, "=");
// 		new_env[j] = ft_strjoin(new_env[j], env1->value);
// 		env1 = env1->next;
// 	}
// 	new_env[j] = NULL;
// 	return(new_env);
// }
