#include "../inc/minishell.h"

int	handle_redirection(t_token *tokens)
{
	int	i;
	int	fd;

	i = 0;
	while (tokens[i].type != END)
	{
		if (tokens[i].type == REDIRECT_IN)
		{
			fd = open(tokens[i + 1].value, O_RDONLY);
			if (fd == -1)
				return (-1);          // Handle error if file cannot be opened
			dup2(fd, STDIN_FILENO); // Redirect input to the file
			close(fd);
			i += 2; // Skip the redirection and filename
		}
		else if (tokens[i].type == REDIRECT_OUT)
		{
			fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			dup2(fd, STDOUT_FILENO); // Redirect output to the file
			close(fd);
			i += 2;
		}
		else if (tokens[i].type == REDIRECT_APPEND)
		{
			fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i += 2;
		}
		else if (tokens[i].type == HEREDOC)
		{
			// Handle heredoc logic, such as reading input until a specific delimiter is found
		}
		else
		{
			i++; // Move to the next token
		}
	}
	return (0);
}

int	parse_input(const char *input)
{
	int		i;
	char	*expanded;

	t_token *tokens = tokenize_input(input); // Tokenize the input
	i = 0;
	// Expand environment variables
	while (tokens[i].type != END)
	{
		if (tokens[i].type == ENV_VAR)
		{
			expanded = expand_env_var(tokens[i].value);
			free(tokens[i].value);
			tokens[i].value = expanded;
		}
		i++;
	}
	// Handle redirections
	if (handle_redirection(tokens) == -1)
		return (-1);
	// Handle pipes
	if (handle_pipes(tokens) == -1)
		return (-1);
	return (0);
}
