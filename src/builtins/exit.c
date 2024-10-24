/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:09:46 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/22 11:17:33 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Checks if a string represents a valid number.
@param s The string to check.
@return true if the string represents a number, false otherwise.
*/
static bool	ft_isnbr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

/*
@brief Skips whitespace in a string and checks for a sign.
@param s The string to process.
@param i Pointer to the current index in the string.
@param sign Pointer to the sign variable.
@return None.
*/
static void	ft_getsign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

/*
@brief Parses the number from the string and handles overflow.
@param s The string to parse.
@param i Pointer to the current index in the string.
@param sign The sign of the number (1 or -1).
@param mini Pointer to the mini structure for cleanup on error.
@return The parsed number.
*/
static unsigned long long	ft_parse_number(char *s, int *i, int sign,
		t_mini *mini)
{
	unsigned long long	result;

	result = 0;
	while (s[*i])
	{
		result = (result * 10) + (s[*i] - '0');
		if (result > LONG_MAX)
		{
			ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(ft_clean_ms(mini), exit(255));
		}
		(*i)++;
	}
	return (result * sign);
}

/*
@brief Converts a string to an integer, with error handling for invalid input.
@param s The string to convert.
@param exit_s Pointer to the exit status variable to be updated on error.
@param mini Pointer to the mini structure for cleanup on error.
@return The integer value of the string, modulo 256.
*/
static int	ft_exittoi(char *s, int *exit_s, t_mini *mini)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_getsign(s, &i, &sign);
	if (!ft_isnbr(s + i))
	{
		*exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(ft_clean_ms(mini), exit(*exit_s));
	}
	result = ft_parse_number(s, &i, sign, mini);
	return (result % 256);
}

/*
@brief Handles the exit command for the shell.
@param args The array of arguments passed to the exit command.
@param exit_s Pointer to the exit status variable to be updated.
@return None.
*/
void	ft_exit(char **args, t_mini *mini)
{
	int	exit_s;

	exit_s = mini->exit_s;
	if (args[1])
	{
		if (args[2] && ft_isnbr(args[1]))
		{
			exit_s = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS,
					NULL});
			(ft_clean_ms(mini), exit(exit_s));
		}
		else
			exit_s = ft_exittoi(args[1], &mini->exit_s, mini);
	}
	(ft_clean_ms(mini), exit(exit_s));
}
