#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_parser_state	parser_state;
	t_ast_node		*ast;

	while (1)
	{
		// Print shell prompt using ft_printf
		ft_printf("trash$ ");
		// Read user input
		line = readline(NULL);
		if (!line)
		{
			break ; // Exit on EOF (Ctrl+D)
		}
		// Tokenize the input
		parser_state.tokens = tokenize(line);
		parser_state.current_token = 0;
		if (parser_state.tokens == NULL)
		{
			ft_dprintf(2, "Error: Failed to tokenize input.\n");
			free(line);
			continue ;
		}
		// Parse the expression using precedence climbing
		ast = parse_expression(&parser_state, 0);
		if (ast == NULL)
		{
			ft_dprintf(2, "Error: Failed to parse expression.\n");
		}
		else
		{
			// Evaluate or execute the AST
			evaluate_ast(ast);
			// Free the AST memory after execution
			free_ast(ast);
		}
		// Free the tokens and the input line
		free_tokens(parser_state.tokens);
		free(line);
	}
	return (0);
}
