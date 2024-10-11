#include "../inc/minishell.h"

/*
@brief Sets the type for a token based on its value and separator status.
@param token The token to set the type for.
@param sep The separator flag to determine how to categorize the token.
@details This function compares the token value with various known symbols (like ">", ">>", etc.) 
to assign the appropriate type to the token, such as TRUNC, APPEND, CMD, ARG, etc.
@return None.
*/
void	type_arg(t_token *token, int sep)
{
	if (ft_strcmp(token->value, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->value, ">") == 0 && sep == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->value, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->value, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->value, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->value, ";") == 0 && sep == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

/*
@brief Allocates the required size for the next token in the input line.
@param line The input line being tokenized.
@param i A pointer to the current index in the input line.
@details This function calculates the necessary space to allocate for a token,
handling escape sequences and quotes, to ensure proper memory allocation.
@return The number of characters required to allocate space for the next token.
*/
int		next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

/*
@brief Extracts the next token from the input line.
@param line The input line being tokenized.
@param i A pointer to the current index in the input line.
@details This function reads through the input line, handling escape sequences and quotes,
and allocates memory for the token's value before returning the new token.
@return A pointer to the newly created token, or NULL if memory allocation fails.
*/
t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->value = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->value[j++] = line[(*i)++];
		else
			token->value[j++] = line[(*i)++];
	}
	token->value[j] = '\0';
	return (token);
}

/*
@brief Tokenizes the input line into a linked list of tokens.
@param line The input line to tokenize.
@details This function reads through the input line, creating and linking tokens,
handling separators, and categorizing each token.
@return A pointer to the first token in the linked list, or NULL if no tokens are found.
*/
t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skipspace(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skipspace(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
