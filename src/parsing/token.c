#include "../inc/minishell.h"

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	squish_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = (prev) ? prev->next : mini->start;
			prev = (prev) ? prev : token;
			prev->next->prev = token;
			prev->next = (mini->start->prev) ? prev->next : token;
			mini->start = (mini->start->prev) ? mini->start->prev : mini->start;
		}
		token = token->next;
	}
}

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

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
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
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

int	add_token(t_token *tokens, int count, t_token_type type, const char *value)
{
	if (count >= MAX_TOKENS - 1)
		// Handle error: Token limit exceeded
		return (-1);
	tokens[count].type = type;
	tokens[count].value = ft_strdup(value); // Add the new token
	tokens[count + 1].type = END; // Mark the end of tokens
	return (count + 1); // Return the updated count of tokens
}

int	tokenize_input(const char *input, t_token *tokens)
{
	int	i;
	int	start;
	int	start;

	i = 0;
	int token_count = 0; // Keep track of the number of tokens
	while (input[i] != '\0')
	{
		// Skip whitespace
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
		{
			token_count = add_token(tokens, token_count, PIPE, "|");
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			token_count = add_token(tokens, token_count, HEREDOC, "<<");
			i += 2;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				token_count = add_token(tokens, token_count,
						REDIRECT_APPEND, ">>");
				i += 2;
			}
			else
			{
				token_count = add_token(tokens, token_count, REDIRECT_OUT,
						">");
				i++;
			}
		}
		else if (input[i] == '<')
		{
			token_count = add_token(tokens, token_count, REDIRECT_IN,
					"<");
			i++;
		}
		else if (input[i] == '\'')
		{
			token_count = add_token(tokens, token_count, QUOTE_SINGLE,
					"'");
			i++;
		}
		else if (input[i] == '"')
		{
			token_count = add_token(tokens, token_count, QUOTE_DOUBLE,
					"\"");
			i++;
		}
		else if (input[i] == '$')
		{
			start = i;
			i++;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++; // Read the environment variable name
			token_count = add_token(tokens, token_count, ENV_VAR,
					ft_strndup(&input[start], i - start));
		}
		else
		{
			start = i;
			while (!ft_isspace(input[i]) && input[i] != '|' && input[i] != '<'
				&& input[i] != '>' && input[i] != '\'' && input[i] != '"'
				&& input[i] != '\0')
			{
				i++; // Read the word token
			}
			token_count = add_token(tokens, token_count, WORD,
					ft_strndup(&input[start], i - start));
		}
		if (token_count == -1)
		{
			// Handle error (e.g., token limit exceeded)
			return (-1);
		}
	}
	return (token_count); // Return the total number of tokens
}
