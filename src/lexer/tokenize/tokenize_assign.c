#include "minishell.h"

int	ft_append_assignment(char **line_ptr, t_token **token_list)
{
	char		*tmp_line;
	char		*value;
	t_token		*token;
	size_t		i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && tmp_line[i] != ' ' && tmp_line[i] != '\t' 
		&& tmp_line[i] != '|' && tmp_line[i] != '<' && tmp_line[i] != '>')
		i++;

	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_ASSIGNMENT);
	if (!token)
		return (free(value), 0);

	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}

bool	ft_is_assignment(const char *str)
{
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	if (!equal_pos || equal_pos == str || !*(equal_pos + 1))
		return (false);
	return (true);
}
