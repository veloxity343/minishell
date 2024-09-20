/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:21 by chtan             #+#    #+#             */
/*   Updated: 2024/09/16 17:18:29 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"
// this is the struct of token part
/*
ttypedef enum e_token_type
{
	TOKEN_WORD,            // General word or command
	TOKEN_PIPE,            // Pipe (|)
	TOKEN_REDIRECT_IN,     // Input redirection (<)
	TOKEN_REDIRECT_OUT,    // Output redirection (>)
	TOKEN_REDIRECT_APPEND, // Output redirection append (>>)
	TOKEN_HEREDOC,         // Here document (<<)
	TOKEN_QUOTE_SINGLE,    // Single quote (')
	TOKEN_QUOTE_DOUBLE,    // Double quote (")
	TOKEN_ENV_VAR,         // Environment variable ($)
	TOKEN_END              // End of tokens
}	t_token_type;

// Struct for a token
typedef struct s_token
{
	t_token_type type; // Type of token
	char *value;       // Value of the token (e.g., the command or file name)
}	t_token;

*/
/*
	requirement for execute
	1) token type
	2) command
	3) arguments
*/
/*
this is the main function of exec part
15/9) cause i can't comfirm how the token gonna pass to me but now i know
and also figure out the simple exec() function
*/

static int ft_check()
{
	;
}

int exec_main(t_token *tokens)
{
	ft_check(tokens->type);// function not complete
}
