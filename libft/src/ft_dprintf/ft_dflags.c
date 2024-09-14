/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dflags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:30:14 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/08 11:30:16 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

dt_flags	ft_dflags_init(void)
{
	dt_flags	flags;

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

dt_flags	ft_dflag_left(dt_flags flags)
{
	flags.left = 1;
	flags.zero = 0;
	return (flags);
}

dt_flags	ft_dflag_digit(char c, dt_flags flags)
{
	if (flags.star == 1)
		flags.width = 0;
	flags.width = (flags.width * 10) + (c - '0');
	return (flags);
}

dt_flags	ft_dflag_width(va_list args, dt_flags flags)
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

int	ft_dflag_precision(const char *str, int i, va_list args, dt_flags *flags)
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
