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

#endif
