#include "../inc/minishell.h"

int	main(void)
{
	char	*input;
	t_token	tokens[MAX_TOKENS];
	int		token_count;

	// Display a prompt in an infinite loop until the user exits the shell
	while (1)
	{
		input = readline("minishell> "); // Display shell prompt
		if (input == NULL)
		{
			ft_printf("\n"); // Handle EOF (Ctrl-D) gracefully
			break ;
		}
		// Add input to history
		if (*input)
			add_history(input);
		// Remove trailing newline if it exists
		input[ft_strcspn(input, "\n")] = 0;
		// Check for empty input (e.g., when just pressing Enter)
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		// Tokenize and parse the input
		token_count = tokenize_input(input, tokens);
		free(input); // Free the input buffer after tokenization
		if (token_count == -1)
		{
			ft_dprintf(2, "Error: Token limit exceeded\n");
			continue ; // Skip to the next command
		}
		// Parse the tokens using precedence climbing logic
		if (parse_input(tokens) == -1)
		{
			ft_dprintf(2, "Error: Parsing failed\n");
			continue ; // Skip to the next command
		}
		// Placeholder for future execution logic
		// Execute the commands after parsing is complete
		// Handle built-in commands or external commands (to be added)
	}
	return (0);
}
