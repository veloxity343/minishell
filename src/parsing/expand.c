/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:28:26 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:28:28 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Copies a variable's value from the environment to a new argument string.
@details This function takes a destination string,
	an environment variable value,
and a starting position, and copies the value of the environment variable into
the destination string starting at the specified position.
@param new_arg A pointer to the destination string where the variable value will be copied.
@param env_value A pointer to the source string (environment variable value) to copy from.
@param pos The position in the destination string to start copying.
@returns The number of characters copied from the environment variable value.
*/
static int	varlcpy(char *new_arg, const char *env_value, int pos)
{
	int	i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

/*
@brief Inserts the value of an environment variable into the expansions structure.
@details This function retrieves the value of an environment variable given its name,
copies it into the new argument string,
	and manages the index for future insertions.
It also handles special cases for the `$?` variable and adjusts the index based on
the character type that follows the variable.
@param ex A pointer to the expansions structure containing the state of the expansion process.
@param arg A pointer to the string that contains the variable name to expand.
@param env A pointer to the linked list of environment variables.
@param ret The return value of the last executed command.
*/
static void	insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	if (env_value)
		ex->i += varlcpy(ex->new_arg, env_value, ex->i);
	else
		ex->i += 0;
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

/*
@brief Expands variables in a given string based on the environment variables.
@details This function processes a string for variable expansions by looking for
`$` characters, retrieving the corresponding environment variable values, and
constructing a new argument string with the expanded values.
@param arg A pointer to the string that may contain variable references.
@param env A pointer to the linked list of environment variables.
@param ret The return value of the last executed command.
@returns A pointer to the newly allocated string with expanded variable values,
or NULL if allocation fails.
*/
char	*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	if (!(ex.new_arg = malloc(sizeof(char) * new_arg_len + 1)))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == '$')
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
