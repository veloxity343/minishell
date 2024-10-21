/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:27:59 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:43:36 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Prints an error message for the export command.
@param error The error code indicating the type of error.
@param arg The argument associated with the error.
@details Depending on the error code,
	this function will print a relevant error message
to STDERR, including invalid context or invalid identifiers.
@return Returns 1 to indicate an error occurred.
*/
static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (1);
}

/*
@brief Adds a new environment variable to the environment linked list.
@param value The environment variable to add.
@param env The head of the environment linked list.
@details If the environment linked list is empty, it initializes the first node.
Otherwise, it creates a new node and adds it to the end of the list.
@return Returns 0 on success, or -1 on allocation failure.
*/
int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

/*
@brief Extracts the environment variable name from a given string.
@param dest The destination string where the variable name will be stored.
@param src The source string containing the environment variable.
@details This function copies the variable name from the
	source string to the destination
until it reaches the '=' character or the end of the string.
@return Returns the destination string containing the variable name.
*/
char	*get_env_name(char *dest, const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
@brief Checks if a given variable name exists in the environment.
@param env The head of the environment linked list.
@param args The argument string representing the variable.
@details This function compares the variable name extracted from args with names
in the environment linked list. If found,
	it updates the value associated with that variable.
@return Returns 1 if the variable exists and was updated, or 0 if not found.
*/
int	is_in_env(t_env *env, char *args)
{
	char	*var_name;
	char	*env_name;

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/*
@brief Exports an environment variable or displays all exported variables.
@param args An array of strings representing the command arguments.
@param env The head of the environment linked list.
@param muted The head of the muted environment linked list.
@details This function checks if the export command is being
	used to add a variable or display existing ones. If adding,
	it validates the variable, handles errors, and adds the
	variable to the environment and muted lists as needed.
@return Returns 0 on success.
*/
int	ft_export(char **args, t_env *env, t_env *muted)
{
	int	new_env;
	int	error_ret;

	new_env = 0;
	if (!args[1])
		return (print_sorted_env(muted), 0);
	else
	{
		error_ret = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		if (error_ret == 2)
			new_env = 1;
		else
			new_env = is_in_env(env, args[1]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				env_add(args[1], env);
			env_add(args[1], muted);
		}
	}
	return (0);
}
