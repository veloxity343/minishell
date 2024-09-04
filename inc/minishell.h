#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_dprintf.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_OPERATOR,
	TOKEN_NUMBER,
	TOKEN_IDENTIFIER,
	TOKEN_PARENTHESIS_OPEN,
	TOKEN_PARENTHESIS_CLOSE,
	TOKEN_END
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
}						t_token;

typedef enum e_associativity
{
	LEFT_ASSOCIATIVE,
	RIGHT_ASSOCIATIVE
}						t_associativity;

typedef struct s_operator
{
	char				*symbol;
	int					precedence;
	t_associativity		associativity;
}						t_operator;

typedef enum e_node_type
{
	NODE_OPERATOR,
	NODE_NUMBER,
	NODE_IDENTIFIER
}						t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	union
	{
		t_operator		*operator;
		char			*value;
	} data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_parser_state
{
	t_token				*tokens;
	int					current_token;
}						t_parser_state;

#endif
