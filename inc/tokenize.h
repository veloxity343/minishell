#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stddef.h>

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_IN_REDIR,
	T_OUT_REDIR,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_O_PAREN,
	T_C_PAREN,
	T_NL,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_token				*ft_new_token(char *value, t_token_type type);
void				ft_token_list_add_back(t_token **lst, t_token *new_token);
void				ft_clear_token_list(t_token **lst);

int					ft_is_quote(char c);
int					ft_is_separator(char *s);
void				ft_skip_spaces(char **line);
bool				ft_skip_quotes(char *line, size_t *i);
void				ft_print_quote_err(char c, t_mini *mini);

int					ft_append_separator(t_token_type type, char **line_ptr,
						t_token **token_list);
int					ft_append_identifier(char **line_ptr, t_token **token_list);
int					ft_handle_separator(char **line_ptr, t_token **token_list);
t_token				*ft_tokenization_handler(t_mini *mini, char *line);
t_token				*ft_tokenize(t_mini *mini);

#endif
