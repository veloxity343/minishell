/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:31 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 16:41:24 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_dprintf.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "parse.h"
# include "tokenize.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "trash ▸ "

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFFER_SIZE 4096

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}					t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}					t_err_no;

typedef struct s_err
{
	t_err_no		no;
	t_err_msg		msg;
	char			*cause;
}					t_err;

typedef struct s_path
{
	t_err			err;
	char			*path;
}					t_path;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_ast_dir
{
	TD_LEFT,
	TD_RIGHT
}					t_ast_dir;

typedef struct s_mini
{
	char			*line;
	t_token			*tokens;
	t_token			*curr_token;
	t_node			*ast;
	int				exit_s;
	bool			sigint_child;
	t_parse_err		parse_err;
	int				stdin;
	int				stdout;
	char			**env_var;
	t_env			*env;
	t_env			*env_muted;
	bool			heredoc_sigint;
	struct termios	ori_term;
}					t_mini;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_sig;

extern t_sig		g_sig;

/* BUILTINS */

int					ft_run_builtin(char **args, t_mini *mini);
bool				ft_isbuiltin(char *arg);

int					update_oldpwd(t_env *env);
int					ft_cd(char **args, t_env *env);

int					ft_echo(char **args);

char				*ft_get_env_val(t_mini *mini, char *key);
bool				ft_env_entry_exists(t_mini *mini, char *key);
void				ft_update_env(t_mini *mini, char *key, char *value,
						bool create);

char				*ft_extract_key(char *str);
char				*ft_extract_value(char *str);
void				ft_init_env(t_mini *mini);
int					ft_env(t_mini *mini);

void				ft_exit(char **args, t_mini *exit_s);

int					env_add(const char *value, t_env *env);
char				*get_env_name(char *dest, const char *src);
int					is_in_env(t_env *env, char *args);
int					ft_export(char **args, t_env *env, t_env *muted);

char				*get_env_path(t_env *env, const char *var, size_t len);

int					ft_pwd(void);

int					ft_unset(char **args, t_mini *mini);

/* CLEANING */

void				ft_clean_ms(t_mini *mini);
void				ft_clear_io_list(t_io_node **lst);
void				ft_clear_cmd_node(t_node *node);
void				ft_recursive_clear_ast(t_mini *mini, t_node *node);
void				ft_clear_ast(t_mini *mini, t_node **ast);
void				*ft_garbage_collector(void *ptr, bool clean);

/* EXEC */

int					ft_err_msg(t_err err);

int					ft_out(t_io_node *io_list, int *status);
int					ft_in(t_io_node *io_list, int *status);
int					ft_append(t_io_node *io_list, int *status);

bool				ft_is_delimiter(char *delimiter, char *str);

int					ft_get_exit_status(int status);
int					ft_exec_node(t_mini *mini, bool piped);

t_err				ft_check_exec(char *file, bool cmd);
t_err				ft_check_read(char *file);
t_err				ft_check_write(char *file);

int					ft_check_redirection(t_node *node);
void				ft_reset_stds(bool piped);
int					ft_exec_simple_cmd(t_mini *mini, bool piped);

t_path				ft_get_path(char *cmd, t_env *env);

void				ft_init_tree(t_node *node);
void				ft_heredoc(t_io_node *io, int p[2]);

/* EXPANDER */

char				*ft_clean_empty_strs(char *str);

bool				ft_is_valid_var_char(char c);
char				*ft_handle_normal_str(char *str, size_t *i);
char				*ft_handle_squotes(char *str, size_t *i);
char				*ft_handle_dquotes(char *str, size_t *i);

char				*ft_handle_dollar(char *str, size_t *i);
char				**ft_expand(char *str);

char				**ft_expander_split(char const *s);

void				ft_heredoc_expander(char *str, int fd);

/* SIGNALS */

void				sig_quit(int code);
void				sig_int(int code);
void				sig_init(void);

#endif
