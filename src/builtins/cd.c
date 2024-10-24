/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:09:48 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 18:42:12 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_pwd(t_mini *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_update_env(mini, "PWD", cwd, false);
	free(cwd);
	return (0);
}

static int	ft_cd_home(t_mini *mini)
{
	char	*home;

	ft_update_env(mini, "OLDPWD", ft_get_env_val(mini, "PWD"), false);
	home = ft_get_env_val(mini, "HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == -1)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (ft_update_env(mini, "PWD", home, false), 0);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(t_mini *mini, char *path)
{
	if (!path)
		return (ft_cd_home(mini));
	if (chdir(path) == -1)
		return (ft_cd_err_msg(path));
	ft_update_env(mini, "OLDPWD", ft_get_env_val(mini, "PWD"), false);
	return (ft_change_pwd(mini));
}
