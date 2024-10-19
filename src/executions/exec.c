/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:21 by chtan             #+#    #+#             */
/*   Updated: 2024/10/19 08:52:58 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/exec.h"
#include "../inc/define_lib.h"

/*
	executition main function
	after parsing, will pass the given token to this function
	the function is to separate command to differnet type of exec
*/
int	ft_exec(t_token *token, t_mini *mini, char **envp)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if (!temp->type)
		{
			error_msg("no command found");
			return (-1);
		}
		temp = temp->next; // error checking
	}
	while (token && token->type == CMD) // Ensure token is valid and type is CMD
	{
		if (ft_isbuiltin(token->value))
		{
			run_builtin(token->value, mini);
		}
		else
		{
			char **array = tokenize_command(token->value); // You should have a function that converts value into args array
			exec(array, envp); // Assuming exec is a wrapper for execve
		}
		token = token->next; // Move to the next token
	}
	return (0);
}

/*
	requirement for execute
	1) token type
	2) command
	3) arguments
	
	when using exeve to execute, -1 will be error
	
	i think better put the exit at the function that call exec
	cause i also need to return the numbers.
	will need to exit with exit code 127 for command not found
*/
int	exec(char **array, char **envp)
{
	int num;
	int status;

	num = -1;
	status = 0;
	
	while (array[++num])
	{
		status = execve(array[num], array, envp);
		if (check_status(status) == FALSE)
		{
			num = ft_dprintf(2, "command not found!");
			//exit_sig(0);
		}
	}
	return (num);
}

bool check_status(int status)
{
	if (status == -1)
	{
		ft_dprintf(2, "command not found!");
		return (FALSE);
	}
	return (TRUE);
}
