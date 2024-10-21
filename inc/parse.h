/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:12:09 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:12:10 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>

typedef enum e_node_type
{
	N_PIPE,
	N_CMD,
}						t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}						t_io_type;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}						t_parse_err_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}						t_io_node;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}						t_parse_err;

void					ft_set_parse_err(t_mini *mini, t_parse_err_type type);
void					ft_handle_parse_err(t_mini *mini);

bool					ft_get_io_list(t_mini *mini, t_io_node **io_list);
bool					ft_join_args(t_mini *mini, char **args);
t_node					*ft_get_simple_cmd(t_mini *mini);

t_io_type				ft_get_io_type(t_token_type type);
t_node					*ft_new_node(t_node_type type);
t_io_node				*ft_new_io_node(t_token_type type, char *value);
void					ft_append_io_node(t_io_node **lst, t_io_node *new);

void					ft_get_next_token(t_mini *mini);
bool					ft_curr_token_is_binop(t_mini *mini);
bool					ft_is_redir(t_token_type type);

t_node					*ft_parse(t_mini *mini);
t_node					*ft_expression(t_mini *mini, int min_prec);
t_node					*ft_term(t_mini *mini);
t_node					*ft_combine(t_mini *mini, t_token_type op, t_node *left,
							t_node *right);

#endif