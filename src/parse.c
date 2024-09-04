#include "minishell.h"

t_ast_node	*parse_primary(t_parser_state *state)
{
	t_token		*token;
	t_ast_node	*node;

	token = &state->tokens[state->current_token];
	if (token->type == TOKEN_NUMBER || token->type == TOKEN_IDENTIFIER)
	{
		node = malloc(sizeof(t_ast_node)); // new AST
		node->type = (token->type == TOKEN_NUMBER) ? NODE_NUMBER : NODE_IDENTIFIER;
		node->data.value = strdup(token->value); // Copy token value to node
		node->left = NULL; // No left or right children for primary expressions
		node->right = NULL;
		state->current_token++;
		return (node);
	}
	// Handle parenthesized expressions
	else if (token->type == TOKEN_PARENTHESIS_OPEN)
	{
		state->current_token++; // Skip the opening parenthesis
		t_ast_node *node = parse_expression(state, 0);
			// Start parsing the expression inside parentheses
		if (state->tokens[state->current_token].type == TOKEN_PARENTHESIS_CLOSE)
		{
			state->current_token++; // Skip the closing parenthesis
			return (node); // Return the parsed node
		}
	}
	return (NULL);
}

t_ast_node	*parse_expression(t_parser_state *state, int min_precedence)
{
	t_ast_node	*lhs;
	t_token		*token;
	t_operator	*op;
	int			next_precedence;
	t_ast_node	*rhs;
	t_ast_node	*new_lhs;

	lhs = parse_primary(state); // Parse the left-hand side expression
	while (1)
	{
		token = &state->tokens[state->current_token]; // Current token
		op = get_operator(token); // Operator
		// If no operator or its precedence is lower than the minimum, break the loop
		if (op == NULL || op->precedence < min_precedence)
			break ;
		state->current_token++;
		// Determine the precedence for the right-hand side expression
		next_precedence = op->precedence
			+ (op->associativity == LEFT_ASSOCIATIVE ? 1 : 0);
		rhs = parse_expression(state, next_precedence); // Parse rhs
		// Create a new AST node for the operator, with lhs and rhs as children
		new_lhs = malloc(sizeof(t_ast_node));
		new_lhs->type = NODE_OPERATOR;
		new_lhs->data.operator= op;
		new_lhs->left = lhs;
		new_lhs->right = rhs;
		lhs = new_lhs; // The new lhs becomes the entire expression parsed so far
	}
	return (lhs);
}
