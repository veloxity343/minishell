#include "minishell.h"

/*
@brief Checks if a token matches a specific type.
@details This function evaluates whether the provided token is of the specified type.
@param token A pointer to the token to be checked.
@param type The type to compare against.
@returns 1 if the token matches the specified type; otherwise, returns 0.
*/
int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

/*
@brief Checks if a token matches any of the specified types.
@details This function checks if the given token's type matches any character in 
the provided string of types. Each character corresponds to a type constant.
@param token A pointer to the token to be checked.
@param types A string containing type characters to match against.
@returns 1 if the token matches one of the specified types; otherwise, returns 0.
*/
int		match_type(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'C') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
		return (1);
	else if (ft_strchr(types, '+') && is_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(token, END))
		return (1);
	return (0);
}

/*
@brief Checks if a linked list of tokens contains a specific type.
@details This function traverses through the linked list of tokens, checking 
for the presence of a token of the specified type.
@param token A pointer to the first token in the linked list.
@param type The type to search for.
@returns 1 if a token of the specified type is found; otherwise, returns 0.
*/
int		has_type(t_token *token, int type)
{
	while (token)
	{
		if (is_type(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

/*
@brief Checks if there is a PIPE token before an END token in a linked list.
@details This function traverses the linked list of tokens and checks for 
the presence of a PIPE token before encountering an END token.
@param token A pointer to the first token in the linked list.
@returns 1 if a PIPE token is found; otherwise, returns 0.
*/
int		has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

/*
@brief Finds the next token of a specified type, optionally skipping the first one.
@details This function traverses the linked list starting from the given token, 
optionally skipping the first token. It continues until it finds the next token 
of the specified type.
@param token A pointer to the starting token.
@param type The type to search for.
@param skip An integer indicating whether to skip the first token (1 to skip).
@returns A pointer to the next token of the specified type, or NULL if not found.
*/
t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}
