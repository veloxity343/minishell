/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:09:32 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:28:30 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Allocates space for a new line with additional spacing for separators.
@param line The original input line to process.
@details This function calculates how much additional space is needed to insert
spaces around separators and allocates a new string with that space.
@return A newly allocated string with space for separators,
	or NULL if memory allocation fails.
*/
char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

/*
@brief Processes a line and adds spaces around certain characters.
@param line The original input line to process.
@details This function uses space_alloc to create a new string and adds spaces
around separators and special characters like '$' and '>'.
@return A newly formatted string with added spaces,
	or NULL if memory allocation fails.
*/
char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new &&line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

/*
@brief Checks if the input line has any unclosed quotes.
@param mini The minishell structure to update on error.
@param line The line to check for unclosed quotes.
@details This function scans the input line for any unclosed quotes and reports a syntax error if any are found.
@return 1 if there is a syntax error, 0 otherwise.
*/
int	quote_check(t_mini *mini, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("trash: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

/*
@brief Processes the input line to prepare for tokenization.
@param mini The minishell structure to update with tokens and status.
@param line The line to process and tokenize.
@details This function processes the input line, checks for quote errors,
adds spaces around separators, and handles signals before tokenizing the line.
@return None.
*/
void	process_line(t_mini *mini, char **line)
{
	t_token	*token;

	if (*line == NULL && (mini->exit = 1))
		ft_putendl_fd("exit", STDERR);
	if (g_sig.sigint == 1)             // Check the signal status
		mini->ret = g_sig.exit_status; // Update mini->ret accordingly
	if (quote_check(mini, line))
		return ;
	*line = space_line(*line);
	if (*line && (*line)[0] == '$')
		(*line)[0] = (char)(-(*line)[0]);
	mini->start = get_tokens(*line);
	ft_memdel(*line);
	merge_args(mini);
	token = mini->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}

/*
@brief Reads and processes the input line for the minishell.
@param mini The minishell structure to use during processing.
@details This function sets up signal handling, displays a prompt, and processes
the input line by tokenizing it and handling quotes and signals.
@return None.
*/
void	parse(t_mini *mini)
{
	char	*line;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (mini->ret)
		ft_putstr_fd("Error: Last command failed", STDERR);
	else
		ft_putstr_fd("Ready to input", STDERR);
	ft_putstr_fd("trash ▸ ", STDERR);
	line = get_next_line(0);
	process_line(mini, &line);
}
