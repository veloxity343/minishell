#include "minishell.h"

int	ft_append_assignment(char **line_ptr, t_token **token_list)
{
	size_t	i = 0;

	// Identify the length of the assignment token
	while ((*line_ptr)[i] && !ft_is_separator(*line_ptr + i))
		i++;

	// Extract the assignment token
	char *assignment = ft_substr(*line_ptr, 0, i);
	if (!assignment)
		return (0);

	// Create and add the token
	t_token *token = ft_new_token(assignment, T_ASSIGNMENT);
	if (!token)
		return (free(assignment), 0);

	// Move line pointer forward and add token to list
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}
