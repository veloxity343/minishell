#include "minishell.h"

int	set_env_variable(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (current->value != NULL);
		}
		current = current->next;
	}

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
		return (free(new_node->key), free(new_node->value), free(new_node), 0);

	new_node->next = *env;
	*env = new_node;
	return (1);
}

int	ft_parse_assignment(t_mini *mini, t_token *token)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	if (token->type != T_ASSIGNMENT)
		return (0);

	equal_pos = ft_strchr(token->value, '=');
	if (!equal_pos || equal_pos == token->value || !*(equal_pos + 1))
		return (0);

	*equal_pos = '\0';       // Separate key and value in token->value
	key = token->value;
	value = equal_pos + 1;

	if (!set_env_variable(&mini->env, key, value))
		return (*equal_pos = '=', 0);  // Restore '=' if failed

	*equal_pos = '=';
	return (1);
}
