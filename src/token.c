#include "minishell.h"

t_token	*tokenize(const char *input)
{
	int		i;
	int		j;
	t_token	*tokens;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_token) * (strlen(input) + 1));
	while (input[i] != '\0')
	{
		while (isspace(input[i])) // Skip whitespaces
			i++;
		if (isdigit(input[i]))
		{ // Handle numbers
			tokens[j].type = TOKEN_NUMBER;
			tokens[j].value = strdup(&input[i]);
			while (isdigit(input[i]))
				i++;
			j++;
		}
		else if (isalpha(input[i]))
		{ // Handle identifiers
			tokens[j].type = TOKEN_IDENTIFIER;
			tokens[j].value = strdup(&input[i]);
			while (isalpha(input[i]))
				i++;
			j++;
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*'
			|| input[i] == '/')
		{ // Handle operators
			tokens[j].type = TOKEN_OPERATOR;
			tokens[j].value = strndup(&input[i], 1);
			i++;
			j++;
		}
		else if (input[i] == '(')
		{ // Handle open parenthesis
			tokens[j].type = TOKEN_PARENTHESIS_OPEN;
			tokens[j].value = strndup(&input[i], 1);
			i++;
			j++;
		}
		else if (input[i] == ')')
		{ // Handle close parenthesis
			tokens[j].type = TOKEN_PARENTHESIS_CLOSE;
			tokens[j].value = strndup(&input[i], 1);
			i++;
			j++;
		}
		else
		{
			i++; // Unknown character, skip it
		}
	}
	tokens[j].type = TOKEN_END; // End of tokens
	tokens[j].value = NULL;
	return (tokens);
}

t_operator	*get_operator(t_token *token)
{
	t_operator	*op;

	op = malloc(sizeof(t_operator));
	if (strcmp(token->value, "+") == 0)
	{
		op->symbol = "+";
		op->precedence = 1;
		op->associativity = LEFT_ASSOCIATIVE;
	}
	else if (strcmp(token->value, "-") == 0)
	{
		op->symbol = "-";
		op->precedence = 1;
		op->associativity = LEFT_ASSOCIATIVE;
	}
	else if (strcmp(token->value, "*") == 0)
	{
		op->symbol = "*";
		op->precedence = 2;
		op->associativity = LEFT_ASSOCIATIVE;
	}
	else if (strcmp(token->value, "/") == 0)
	{
		op->symbol = "/";
		op->precedence = 2;
		op->associativity = LEFT_ASSOCIATIVE;
	}
	else
	{
		free(op);
		return (NULL);
	}
	return (op);
}
