/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:31 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/15 22:04:20 by rcheong          ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	t_env			*envlst;
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

size_t				size_env(t_env *lst);
char				*env_to_str(t_env *lst);
int					env_init(t_mini *mini, char **env_array);
int					muted_env_init(t_mini *mini, char **env_array);
int					is_env_char(int c);
int					is_valid_env(const char *env);
int					env_value_len(const char *env);
char				*env_value(char *env);
char				*get_env_value(char *arg, t_env *env);
int					str_env_len(char **env);
void				sort_env(char **tab, int env_len);
void				print_sorted_env(t_env *env);
void				increment_shell_level(t_env *env);

char				*expansions(char *arg, t_env *env, int ret);
int					ret_size(int ret);
int					get_var_len(const char *arg, int pos, t_env *env, int ret);
int					arg_alloc_len(const char *arg, t_env *env, int ret);
char				*get_var_value(const char *arg, int pos, t_env *env,
						int ret);

int					ft_isbuiltin(char *command);
int					run_builtin(char **args, t_mini *mini);
int					ft_cd(char **args, t_env *env);
int					ft_echo(char **arg);
int					ft_print_env(t_env *env);
void				mini_exit(t_mini *mini, char **cmd);
int					ft_export(char **args, t_env *env, t_env *secret);
int					is_in_env(t_env *env, char *args);
char				*get_env_name(char *dest, const char *src);
int					env_add(const char *value, t_env *env);
int					ft_pwd(void);
int					ft_unset(char **a, t_mini *mini);

void				ft_close(int fd);
void				reset_std(t_mini *mini);
void				close_fds(t_mini *mini);
void				reset_fds(t_mini *mini);
void				free_token(t_token *start);
void				free_env(t_env *env);
void				free_tab(char **tab);
int					check_line(t_mini *mini, t_token *token);
int					is_last_valid_arg(t_token *token);
int					quotes(char *line, int index);
int					ignore_sep(char *line, int i);
int					is_sep(char *line, int i);
t_token				*next_sep(t_token *token, int skip);
t_token				*prev_sep(t_token *token, int skip);
t_token				*next_run(t_token *token, int skip);
int					is_type(t_token *token, int type);
int					match_type(t_token *token, char *types);
int					has_type(t_token *token, int type);
int					has_pipe(t_token *token);
t_token				*next_type(t_token *token, int type, int skip);

void				sig_init(void);
void				sig_quit(int code);
void				sig_int(int code);

#endif
