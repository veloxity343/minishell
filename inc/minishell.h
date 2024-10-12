/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:26:31 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:50:35 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/ft_dprintf.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include "/usr/include/readline/history.h"
# include "/usr/include/readline/readline.h"
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
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFFER_SIZE 4096

// Enum for tokens
typedef enum e_token_type
{
	EMPTY,	// No token or uninitialized state
	CMD,	// Command token (e.g., 'ls', 'echo')
	ARG,	// Argument token (e.g., '-l', 'file.txt')
	TRUNC,	// Truncate output redirection (>)
	APPEND,	// Append output redirection (>>)
	INPUT,	// Input redirection (<)
	PIPE,	// Pipe token (|) for chaining commands
	END		// End of command (e.g., ';' or newline)
}	t_token_type;

// Struct representing each token in a doubly-linked list for a parsed command.
typedef struct s_token
{
	t_token_type	type;	// Type of token
	char			*value;	// Value of the token (e.g., the command or file name)
	struct s_token	*prev;	// Previous node in ll
	struct s_token	*next;	// Next node in ll
}	t_token;

// Struct representing an environment variable in a linked list.
typedef struct	s_env
{
	char			*value;  // The string value of the environment variable (e.g., "PATH=/usr/bin")
	struct s_env	*next;   // Pointer to the next environment variable in the list
}				t_env;

// Struct representing the state of the minishell.
typedef struct	s_mini
{
	t_token			*start;       // Pointer to the first token in the parsed command list
	t_env			*env;         // Pointer to the environment variable list
	t_env			*muted_env;   // Pointer to muted environment variable list
	int				in;           // Standard input file descriptor
	int				out;          // Standard output file descriptor
	int				fdin;         // File descriptor for input redirection
	int				fdout;        // File descriptor for output redirection
	int				pipin;        // Pipe input file descriptor
	int				pipout;       // Pipe output file descriptor
	int				pid;          // Process ID of the current shell process
	int				charge;       // Status or flag for managing multiple processes
	int				parent;       // Flag indicating if the current process is the parent
	int				last;         // Status of the last executed command
	int				ret;          // Return value of the last executed command
	int				exit;         // Exit status flag for the shell
	int				no_exec;      // Flag to indicate if commands should not be executed
}				t_mini;

// Struct representing signal handling information.
typedef struct	s_sig
{
	int				sigint;        // Flag for handling SIGINT (Ctrl+C)
	int				sigquit;       // Flag for handling SIGQUIT (Ctrl+\)
	int				exit_status;   // Exit status after a signal is received
	pid_t			pid;           // Process ID for the process handling the signal
}				t_sig;

extern t_sig g_sig;

// Struct used for handling expansions within arguments (e.g., $VARIABLE).
typedef struct	s_expansions
{
	char			*new_arg;  // The new argument string after expansions
	int				i;        // Index for iterating through the original string
	int				j;        // Index for iterating through the new string (after expansion)
}				t_expansions;

// parse
void	parse(t_mini *mini);
void	process_line(t_mini *mini, char **line);
int	quote_check(t_mini *mini, char **line);
char	*space_line(char *line);
char	*space_alloc(char *line);

// token
t_token	*get_tokens(char *line);
t_token	*next_token(char *line, int *i);
int		next_alloc(char *line, int *i);
void	type_arg(t_token *token, int sep);

// expansions
char	*expansions(char *arg, t_env *env, int ret);

// args
void	merge_args(t_mini *mini);

// builtins
int		ft_isbuiltin(char *command);
int		run_builtin(char **args, t_mini *mini);
int	ft_cd(char **args, t_env *env);
int	ft_echo(char **arg);
int	ft_print_env(t_env *env);
void	mini_exit(t_mini *mini, char **cmd);
int	ft_export(char **args, t_env *env, t_env *secret);
int	is_in_env(t_env *env, char *args);
char	*get_env_name(char *dest, const char *src);
int	env_add(const char *value, t_env *env);
int		ft_pwd(void);
int	ft_unset(char **a, t_mini *mini);

// tools
void	ft_close(int fd);
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);
void	free_token(t_token *start);
void	free_env(t_env *env);
void	free_tab(char **tab);
int	check_line(t_mini *mini, t_token *token);
int	is_last_valid_arg(t_token *token);
int	quotes(char *line, int index);
int	ignore_sep(char *line, int i);
int	is_sep(char *line, int i);
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_run(t_token *token, int skip);
int		is_type(t_token *token, int type);
int		match_type(t_token *token, char *types);
int		has_type(t_token *token, int type);
int		has_pipe(t_token *token);
t_token	*next_type(t_token *token, int type, int skip);

// sig
void	sig_init(void);
void	sig_quit(int code);
void	sig_int(int code);
void	exit_sig(int sig);
void ignore_signal(int sig);

void			sig_int(int code);
void			sig_quit(int code);
void			sig_init(void);

#endif
