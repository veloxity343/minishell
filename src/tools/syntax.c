#include "minishell.h"

static void	print_syntax_error(t_mini *mini, t_token *token, const char *msg)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
	if (token)
		ft_putstr_fd(token->value, STDERR);
	else
		ft_putstr_fd("newline", STDERR);
	ft_putendl_fd("'", STDERR);
	mini->ret = 258;
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		// Check for invalid token sequence for "TAI"
		if (match_type(token, "TAI") && (!token->next || match_type(token->next,
					"TAIPE")))
		{
			print_syntax_error(mini, token->next, "unexpected token");
			return (0);
		}
		// Check for invalid token sequence for "PE"
		if (match_type(token, "PE") && (!token->prev || !token->next
				|| match_type(token->prev, "TAIPE")))
		{
			print_syntax_error(mini, token, "unexpected token");
			return (0);
		}
		token = token->next; // Proceed to the next token
	}
	return (1); // Return 1 if no errors were found
}
