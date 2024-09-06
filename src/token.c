#include "../inc/minishell.h"

int	add_token(t_token *tokens, int count, t_token_type type, const char *value)
{
	if (count >= MAX_TOKENS - 1)
		// Handle error: Token limit exceeded
		return (-1);
	tokens[count].type = type;
	tokens[count].value = ft_strdup(value); // Add the new token
	tokens[count + 1].type = TOKEN_END; // Mark the end of tokens
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
			token_count = add_token(tokens, token_count, TOKEN_PIPE, "|");
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			token_count = add_token(tokens, token_count, TOKEN_HEREDOC, "<<");
			i += 2;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				token_count = add_token(tokens, token_count,
						TOKEN_REDIRECT_APPEND, ">>");
				i += 2;
			}
			else
			{
				token_count = add_token(tokens, token_count, TOKEN_REDIRECT_OUT,
						">");
				i++;
			}
		}
		else if (input[i] == '<')
		{
			token_count = add_token(tokens, token_count, TOKEN_REDIRECT_IN,
					"<");
			i++;
		}
		else if (input[i] == '\'')
		{
			token_count = add_token(tokens, token_count, TOKEN_QUOTE_SINGLE,
					"'");
			i++;
		}
		else if (input[i] == '"')
		{
			token_count = add_token(tokens, token_count, TOKEN_QUOTE_DOUBLE,
					"\"");
			i++;
		}
		else if (input[i] == '$')
		{
			start = i;
			i++;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++; // Read the environment variable name
			token_count = add_token(tokens, token_count, TOKEN_ENV_VAR,
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
			token_count = add_token(tokens, token_count, TOKEN_WORD,
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
