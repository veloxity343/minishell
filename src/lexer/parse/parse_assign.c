#include "minishell.h"

static int	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_var;

	// Search for the key in the existing environment list
	current = *env;
	while (current)
	{
		// If the key exists, update its value
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				return (0); // Memory allocation failed
			return (1); // Successfully updated
		}
		current = current->next;
	}

	// If the key doesn't exist, create a new environment variable node
	new_var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_var)
		return (0); // Memory allocation failed
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	if (!new_var->key || !new_var->value)
		return (free(new_var->key), free(new_var->value), free(new_var), 0);

	// Append the new variable to the front of the list for simplicity
	new_var->next = *env;
	*env = new_var;
	return (1); // Successfully added new variable
}

int	ft_parse_assignment(t_mini *mini, t_env *env)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	// Ensure the current token is an assignment
	if (mini->curr_token->type != T_ASSIGNMENT)
		return (0);

	// Locate the '=' in the assignment token
	equal_sign = ft_strchr(mini->curr_token->value, '=');
	if (!equal_sign || equal_sign == mini->curr_token->value)
		return (0); // Invalid assignment format

	// Split the token into key and value
	*equal_sign = '\0'; // Null-terminate the key part
	key = mini->curr_token->value; // Key part of the assignment
	value = equal_sign + 1; // Value part of the assignment

	// Set the environment variable
	if (!set_env_value(&env, key, value))
		return (ft_set_parse_err(mini, E_MEM), 0);

	// Move to the next token after processing the assignment
	ft_get_next_token(mini);
	return (1);
}
