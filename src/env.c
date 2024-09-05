#include "minishell.h"

char	*expand_env_var(const char *token)
{
	if (token[0] == '$')
	{
		const char *env_value = getenv(&token[1]);
			// Get the value of the environment variable
		if (env_value != NULL)
			return (ft_strdup(env_value));
				// Return the value of the environment variable
	}
	return (ft_strdup(token));
		// Return the token itself if not an environment variable
}
