/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:27:40 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/12 18:27:41 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief Implements the 'echo' command, printing arguments to the standard output.
@param arg The array of arguments passed to the 'echo' command.
@details This function mimics the behavior of the Unix 'echo' command. It prints
each argument to the standard output, with spaces between them. If the '-n' flag
is provided, it suppresses the trailing newline.
@return Always returns 0.
*/
int	ft_echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (arg_count(arg) > 1)
	{
		while (arg[i] && ft_strcmp(arg[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (arg[i])
		{
			ft_putstr_fd(arg[i], 1);
			if (arg[i + 1] && arg[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}
