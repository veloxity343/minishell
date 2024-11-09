/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:21 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/09 10:16:22 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Checks if a character is a quote.
@param c The character to check.
@return True if the character is a quote, false otherwise.
*/
int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

/*
@brief Checks if a character is a separator.
@param s The character to check.
@return True if the character is a separator, false otherwise.
*/
int	ft_is_separator(char *s)
{
	if (*s == ' ' || *s == '\t' || *s == '<' || *s == '>' || *s == '|'
		|| *s == '(' || *s == ')')
		return (1);
	return (0);
}

/*
@brief Skips spaces in the input line.
@param line The input line.
@return None.
*/
void	ft_skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

/*
@brief Skips quoted strings.
@param line The input line.
@param i The index of the current character.
@return True if a quote was skipped, false otherwise.
*/
bool	ft_skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

/*
@brief Prints an error message for an unexpected quote.
@param c The unexpected quote character.
@return None.
*/
void	ft_print_quote_err(char c)
{
	ft_putstr_fd("trash: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_sig.exit_s = 258;
}
