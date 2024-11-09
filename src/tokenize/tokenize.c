/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:18 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:14:54 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Appends a separator token to the token list.
@param type The type of separator.
@param line_ptr The input line.
@param token_list The linked list of tokens.
@return 1 if successful, 0 otherwise.
*/
int	ft_append_separator(t_token_type type, char **line_ptr,
		t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_HEREDOC || type == T_APPEND)
		(*line_ptr)++;
	return (1);
}

/*
@brief Appends an identifier token to the token list.
@param line_ptr The input line.
@param token_list The linked list of tokens.
@return 1 if successful, 0 otherwise.
*/
int	ft_append_identifier(char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}

/*
@brief Handles the separator token.
@param line_ptr The input line.
@param token_list The linked list of tokens.
@return 1 if successful, 0 otherwise.
*/
int	ft_handle_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (ft_append_separator(T_HEREDOC, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (ft_append_separator(T_APPEND, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (ft_append_separator(T_IN_REDIR, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (ft_append_separator(T_OUT_REDIR, line_ptr, token_list) && 1);
	else
		return (ft_append_separator(T_PIPE, line_ptr, token_list) && 1);
}

/*
@brief Assigns the token type based on the input line.
@param line The input line.
@details Tokenizes the input line based on the separators.
@return The linked list of tokens.
*/
t_token	*ft_tokenization_handler(char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (ft_clear_token_list(&token_list), NULL);
		if (ft_isspace(*line))
			ft_skip_spaces(&line);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "(", 1)
			|| !ft_strncmp(line, ")", 1))
			error = (!ft_handle_separator(&line, &token_list) && 1);
		else
			error = (!ft_append_identifier(&line, &token_list) && 1);
	}
	return (token_list);
}

/*
@brief Tokenizes the input line.
@param mini The minishell structure containing the current state.
@return The linked list of tokens.
*/
t_token	*ft_tokenize(t_mini *mini)
{
	char	*line;
	t_token	*token_list;

	line = mini->line;
	token_list = ft_tokenization_handler(line);
	free(line);
	mini->line = NULL;
	return (token_list);
}
