/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:09:48 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 23:34:15 by chtan            ###   ########.fr       */
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

/*
@brief Changes the current working directory to the home directory.
@param mini The minishell structure.
@return 0 on success, 1 on failure.
*/
static int	ft_cd_home(t_mini *mini)
{
	char	*home;

	ft_update_env(mini, "OLDPWD", ft_get_env_val(mini, "PWD"), false);
	home = ft_get_env_val(mini, "HOME");
	if (!home)
		return (ft_putstr_fd("trash: cd: HOME not set\n", 2), 1);
	if (chdir(home) == -1)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (ft_update_env(mini, "PWD", home, false), 0);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("trash: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

/*
    the function need the env variable OLDPWD to be updated
    the oldpwd will auto fill into the env so i just need to take the env
    and change the directory to the oldpwd
*/
static int	ft_go_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	int		sig;

	oldpwd = ft_get_env_val(mini, "OLDPWD");
	if (!oldpwd)
		return (ft_putstr_fd("trash: cd: OLDPWD not set\n", 2), 1);
	sig = chdir(oldpwd);
	if (sig == -1)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	ft_putstr_fd(oldpwd, 1);
	ft_putchar('\n');
	ft_update_env(mini, "PWD", oldpwd, false);
	return (0);
}

int	ft_cd(t_mini *mini, char *path)
{
	if (!path)
		return (ft_cd_home(mini));
	if (strcmp(path, "-") == 0)
		return (ft_go_oldpwd(mini));
	if (chdir(path) == -1)
		return (ft_cd_err_msg(path));
	ft_update_env(mini, "OLDPWD", ft_get_env_val(mini, "PWD"), false);
	return (ft_change_pwd(mini));
}
