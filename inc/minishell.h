/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:31 by rcheong           #+#    #+#             */
/*   Updated: 2024/11/03 16:38:30 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/inc/ft_dprintf.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/libft.h"

# define PROMPT "trash ▸ "

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_ASSIGNMENT,
	T_IN_REDIR,
	T_OUT_REDIR,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_NL,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}						t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}						t_err_no;

typedef struct s_err
{
	t_err_no			no;
	t_err_msg			msg;
	char				*cause;
}						t_err;

typedef struct s_path
{
	t_err				err;
	char				*path;
}						t_path;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_ast_dir
{
	TD_LEFT,
	TD_RIGHT
}						t_ast_dir;

typedef struct s_mini
{
	char				*line;
	t_token				*tokens;
	t_token				*curr_token;
	t_node				*ast;
	t_parse_err			parse_err;
	int					stdin;
	int					stdout;
	char				**env_var;
	t_env				*env;
	t_env				*env_muted;
	struct termios		ori_term;
}						t_mini;

typedef struct s_sig
{
	bool				sigint;
	int					exit_s;
	bool				heredoc_sigint;
}						t_sig;

extern t_sig			g_sig;

/* BUILTINS */

int						ft_run_builtin(char **args, t_mini *mini);
bool					ft_isbuiltin(char *arg);

int						ft_cd(t_mini *mini, char *path);

int						ft_echo(char **args);

char					*ft_get_env_val(t_mini *mini, char *key);
bool					ft_env_entry_exists(t_mini *mini, char *key);
void					ft_update_env(t_mini *mini, char *key, char *value,
							bool create);

char					*ft_extract_key(char *str);
char					*ft_extract_value(char *str);
void					ft_init_env(t_mini *mini);
int						ft_env(t_mini *mini);

void					ft_exit(char **args, t_mini *mini);

int	ft_parse_assignment(t_mini *mini, t_token *token);
int	ft_append_assignment(char **line_ptr, t_token **token_list);
bool	ft_is_assignment(const char *str);
int						ft_check_key(const char *str);
int						ft_export(t_mini *mini, char **argv);

char					*get_env_path(t_env *env, const char *var, size_t len);

int						ft_pwd(void);

int						ft_unset(char **args, t_mini *mini);

/* CLEAN */

void					ft_free_char2(char **tofree);
void					ft_free_char3(char ***tofree);
void					ft_clean_ms(t_mini *mini);
void					ft_clear_io_list(t_io_node **lst);
void					ft_clear_cmd_node(t_node *node);
void					ft_recursive_clear_ast(t_mini *mini, t_node *node);
void					ft_clear_ast(t_mini *mini, t_node **ast);
void					*ft_garbage_collector(void *ptr, bool clean);

/* EXEC */

int						ft_err_msg(t_err err);

int						ft_out(t_io_node *io_list, int *status);
int						ft_in(t_io_node *io_list, int *status);
int						ft_append(t_io_node *io_list, int *status);

bool					ft_is_delimiter(char *delimiter, char *str);

int						ft_get_exit_status(int status);
int						ft_exec_node(t_mini *mini, t_node *node, bool piped);

t_err					ft_check_exec(char *file, bool cmd);
t_err					ft_check_read(char *file);
t_err					ft_check_write(char *file);

int						ft_check_redirection(t_node *node);
void					ft_reset_stds(t_mini *mini, bool piped);
int						ft_exec_simple_cmd(t_mini *mini, t_node *node, bool piped);

t_path					ft_get_path(char *cmd, t_mini *mini);

void					ft_init_tree(t_node *node, t_mini *mini);
void					ft_heredoc(t_io_node *io, int p[2], t_mini *mini);
char					**env_update(t_mini **mini);


/* EXPAND */

char					*ft_clean_empty_strs(char *str);

bool					ft_is_valid_var_char(char c);
char					*ft_handle_normal_str(char *str, size_t *i);
char					*ft_handle_squotes(char *str, size_t *i);
char					*ft_handle_dquotes(t_mini *mini, char *str, size_t *i);

char					*ft_handle_dollar(t_mini *mini, char *str, size_t *i);
char					**ft_expand(t_mini *mini, char *str);

char					**ft_expander_split(char const *s);
char					*ft_strip_quotes(char *str);

void					ft_heredoc_expander(t_mini *mini, char *str, int fd);

/* SIGNALS */

void					sig_quit(int code);
void					sig_int(int code);
void					sig_init(void);

/* PARSE */
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

t_node					*ft_parser(t_mini *mini);
t_node					*ft_expression(t_mini *mini);
t_node					*ft_term(t_mini *mini);
t_node					*ft_combine(t_mini *mini, t_node *left, t_node *right);

/* TOKENIZE */

t_token					*ft_new_token(char *value, t_token_type type);
void					ft_token_list_add_back(t_token **lst,
							t_token *new_token);
void					ft_clear_token_list(t_token **lst);

int						ft_is_quote(char c);
int						ft_is_separator(char *s);
void					ft_skip_spaces(char **line);
bool					ft_skip_quotes(char *line, size_t *i);
void					ft_print_quote_err(char c);

int						ft_append_separator(t_token_type type, char **line_ptr,
							t_token **token_list);
int						ft_append_identifier(char **line_ptr,
							t_token **token_list);
int						ft_handle_separator(char **line_ptr,
							t_token **token_list);
t_token					*ft_tokenization_handler(char *line);
t_token					*ft_tokenize(t_mini *mini);

#endif
