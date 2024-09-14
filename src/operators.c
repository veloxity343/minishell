#include "minishell.h"

char	*handle_single_quotes(const char *input, int *i)
{
	int start = ++(*i); // Move past the opening single quote
	while (input[*i] != '\'' && input[*i] != '\0')
		(*i)++; // Find the closing single quote
	if (input[*i] == '\'')
		(*i)++; // Move past the closing single quote
	return (ft_strndup(&input[start], *i - start - 1));
		// Return the literal content inside quotes
}

char	*handle_double_quotes(const char *input, int *i)
{
	int start = ++(*i); // Move past the opening double quote
	while (input[*i] != '"' && input[*i] != '\0')
		(*i)++; // Find the closing double quote
	if (input[*i] == '"')
		(*i)++; // Move past the closing double quote
	return (ft_strndup(&input[start], *i - start - 1));
		// Return the literal content inside quotes
}

int	handle_pipes(t_token *tokens)
{
	int	i;
	int	pipe_fd[2];
	int	prev_fd;

	i = 0;
	prev_fd = -1;
	while (tokens[i].type != TOKEN_END)
	{
		if (tokens[i].type == TOKEN_PIPE)
		{
			pipe(pipe_fd); // Create a pipe
			if (fork() == 0)
			{
				// Child process for the current command
				if (prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
						// Read from previous command's output
					close(prev_fd);
				}
				dup2(pipe_fd[1], STDOUT_FILENO); // Write output to the pipe
				close(pipe_fd[0]);
				// Execute the command
			}
			// Parent process
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
				// Save the pipe's read end for the next command
			i++;
		}
		else
		{
			// Execute non-piped command
			i++;
		}
	}
	if (prev_fd != -1)
		close(prev_fd); // Close any remaining file descriptors
	return (0);
}
