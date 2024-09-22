#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/ft_dprintf.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include "../readline/history.h"
# include "../readline/readline.h"
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

# define MAX_TOKENS 1024

typedef enum e_token_type
{
	WORD,            // General word or command
	PIPE,            // Pipe (|)
	REDIRECT_IN,     // Input redirection (<)
	REDIRECT_OUT,    // Output redirection (>)
	REDIRECT_APPEND, // Output redirection append (>>)
	HEREDOC,         // Here document (<<)
	QUOTE_SINGLE,    // Single quote (')
	QUOTE_DOUBLE,    // Double quote (")
	ENV_VAR,         // Environment variable ($)
	END              // End of tokens
}	t_token_type;

// Struct for a token
typedef struct s_token
{
	t_token_type type; // Type of token
	char *value;       // Value of the token (e.g., the command or file name)
	struct s_token	*prev; // Previous node in ll
	struct s_token	*next; // Next node in ll
}	t_token;

// Struct for a command
typedef struct s_command
{
	char **argv;       // Argument vector (e.g., ["ls", "-l"])
	char *input_file;  // Input redirection file
	char *output_file; // Output redirection file
	int append;        // Flag for output append mode
	int fd_in;         // File descriptor for input redirection
	int fd_out;        // File descriptor for output redirection
	pid_t pid;         // Process ID for executing command
}	t_command;

// Struct for handling pipes
typedef struct s_pipe
{
	int fd[2];           // File descriptors for pipe (fd[0] for reading, fd[1] for writing)
	struct s_pipe *next; // Pointer to the next pipe in the chain
}	t_pipe;

// Struct for storing environment variables
typedef struct s_env
{
	char *key;          // Environment variable key
	char *value;        // Environment variable value
	struct s_env *next; // Pointer to the next environment variable
}	t_env;

// env
char	*expand_env_var(const char *token);

// operators
char	*handle_single_quotes(const char *input, int *i);
char	*handle_double_quotes(const char *input, int *i);
int		handle_pipes(t_token *tokens);

//parse
int		handle_redirection(t_token *tokens);
int		parse_input(const char *input);

//token
int		add_token(t_token *tokens, int count, t_token_type type, const char *value);
int		tokenize_input(const char *input, t_token *tokens);

#endif
