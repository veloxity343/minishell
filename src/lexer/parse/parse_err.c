/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:24:03 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/30 21:15:53 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_parse_err(t_mini *mini, t_parse_err_type type)
{
	mini->parse_err.type = type;
}

void	ft_handle_parse_err(t_mini *mini)
{
	t_parse_err_type	type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_IDENTIFIER", "<", ">", "<<", ">>", "|", "(", ")",
		"newline"};
	type = mini->parse_err.type;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type == E_SYNTAX)
		{
			if (!mini->curr_token)
				token_type = T_NL;
			else
				token_type = mini->curr_token->type;
			ft_putstr_fd("trash: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			g_sig.exit_s = 258;
		}
		ft_clear_ast(mini, &mini->ast);
		ft_bzero(&mini->parse_err, sizeof(t_parse_err));
	}
}
