#include "minishell.h"

/*
@brief Prints an error message related to the 'cd' command.
@param args The array of arguments passed to the 'cd' command.
@details This function prints an error message when the 'cd' command fails. 
If there is an extra argument, it indicates "string not in pwd", otherwise, it prints the system error message.
@return None.
*/
static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

/*
@brief Retrieves the value of an environment variable by its name.
@param env The environment variable list.
@param var The name of the environment variable to retrieve.
@param len The length of the environment variable's name.
@details This function searches through the linked list of environment variables 
and returns the value associated with the variable name `var`.
@return The value of the environment variable, or NULL if not found or allocation fails.
*/
static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

/*
@brief Updates the value of the OLDPWD environment variable.
@param env The environment variable list.
@details This function sets the OLDPWD environment variable to the current working directory.
@return 0 on success, 1 on failure.
*/
static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD =", cwd)))
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (0);
}

/*
@brief Changes the current directory to a specific path based on options.
@param option The option to determine whether to use "HOME" or "OLDPWD" for the path.
@param env The environment variable list.
@details This function changes the current directory based on the provided option: 
0 for "HOME" and 1 for "OLDPWD". If the directory change is successful, the OLDPWD is updated.
@return 0 on success, 1 if the path is not set or an error occurs.
*/
static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("trash : cd: HOME not set", STDERR);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("trash : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

/*
@brief Changes the current directory using the 'cd' command.
@param args The array of arguments passed to the 'cd' command.
@param env The environment variable list.
@details This function processes the 'cd' command. If no argument is provided, it defaults to the "HOME" path. 
If the argument is "-", it switches to the "OLDPWD" path. It updates the OLDPWD variable before changing the directory.
@return 0 on success, or a non-zero error code on failure.
*/
int	ft_cd(char **args, t_env *env)
{
	int	cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}
