#include "minishell.h"

/*
@brief Returns the size of the environment variable name.
@details This function iterates through the provided environment variable string 
until it encounters an '=' character, counting the number of characters before it. 
This helps determine the length of the variable name.
@param env The environment variable string.
@return The size of the variable name, excluding the '=' character.
*/
static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

/*
@brief Frees the memory allocated for a given environment variable node.
@details This function checks if the node to be freed is the only node in the list 
and handles the cleanup accordingly. If it is not the only node, it frees the value 
and the node itself.
@param mini A pointer to the minishell structure containing the environment.
@param env A pointer to the environment variable node to be freed.
*/
static void	free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

/*
@brief Removes an environment variable from the minishell environment.
@details This function searches for the environment variable specified in the 
arguments and removes it from the linked list of environment variables. 
If the variable is found at the head of the list, it updates the head pointer.
@param a The array of command-line arguments where a[1] is the variable to unset.
@param mini A pointer to the minishell structure containing the environment.
@return Returns 0 upon successful completion, or a negative value on failure.
*/
int	ft_unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!(a[1]))
		return (0);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		mini->env = (env->next) ? env->next : mini->env;
		free_node(mini, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
