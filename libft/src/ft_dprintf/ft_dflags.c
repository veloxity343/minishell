/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dflags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:30:14 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 13:22:18 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

t_dflags	ft_dflags_init(void)
{
	t_dflags	flags;

	flags.spec = 0;
	flags.left = 0;
	flags.zero = 0;
	flags.precision = -1;
	flags.width = 0;
	flags.star = 0;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	return (flags);
}

t_dflags	ft_dflag_left(t_dflags flags)
{
	flags.left = 1;
	flags.zero = 0;
	return (flags);
}

t_dflags	ft_dflag_digit(char c, t_dflags flags)
{
	if (flags.star == 1)
		flags.width = 0;
	flags.width = (flags.width * 10) + (c - '0');
	return (flags);
}

t_dflags	ft_dflag_width(va_list args, t_dflags flags)
{
	flags.star = 1;
	flags.width = va_arg(args, int);
	if (flags.width < 0)
	{
		flags.left = 1;
		flags.width *= -1;
	}
	return (flags);
}

int	ft_dflag_precision(const char *str, int i, va_list args, t_dflags *flags)
{
	int	j;

	j = i + 1;
	if (str[j] == '*')
	{
		flags->precision = va_arg(args, int);
		return (j++);
	}
	flags->precision = 0;
	while (ft_isdigit(str[j]))
	{
		flags->precision = (flags->precision * 10) + (str[j] - '0');
		j++;
	}
	return (j);
}
