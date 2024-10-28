/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:47:33 by chtan             #+#    #+#             */
/*   Updated: 2024/10/28 12:47:34 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Allocates memory for the value part of an environment variable.
@param full_value The full string from the environment (e.g., "VAR=value").
@param len The length of the variable name.
@return A newly allocated string containing the variable's value,
	or NULL if allocation fails.
*/
static char	*allocate_value(const char *full_value, size_t len)
{
	char	*value;
	size_t	value_len;

	value_len = ft_strlen(full_value) - len;
	value = malloc(sizeof(char) * (value_len + 1));
	if (!value)
		return (NULL);
	return (value);
}

/*
@brief Extracts the value from an environment string after the variable name.
@param full_value The full string from the environment (e.g., "VAR=value").
@param len The length of the variable name.
@param value The buffer where the extracted value will be stored.
@return None.
*/
static void	extract_value(const char *full_value, size_t len, char *value)
{
	size_t	i;
	size_t	j;

	i = len;
	j = 0;
	while (full_value[i])
		value[j++] = full_value[++i];
	value[j] = '\0';
}

/*
@brief Retrieves the value of an environment variable by its name.
@param env The environment variable list.
@param var The name of the environment variable to retrieve.
@param len The length of the environment variable's name.
@return The value of the environment variable, or NULL if not found.
*/
char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*value;

	while (env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			value = allocate_value(env->value, len);
			if (!value)
				return (NULL);
			extract_value(env->value, len, value);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}
