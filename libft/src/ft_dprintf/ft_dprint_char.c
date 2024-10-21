/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:31:28 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 13:22:27 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_dpad_width(int fd, int width, int size, int zero)
{
	int	count;

	count = 0;
	while (width - size > 0)
	{
		if (zero)
			count += ft_dputchar(fd, '0');
		else
			count += ft_dputchar(fd, ' ');
		width--;
	}
	return (count);
}

int	ft_dprint_char(int fd, int c, t_dflags flags)
{
	int	count;

	count = 0;
	if (flags.left == 1)
	{
		if (c == '\0')
			count += ft_dputchar(fd, '\0');
		else
			count += ft_dputchar(fd, c);
	}
	count += ft_dpad_width(fd, flags.width, 1, flags.zero);
	if (flags.left == 0)
	{
		if (c == '\0')
			count += ft_dputchar(fd, '\0');
		else
			count += ft_dputchar(fd, c);
	}
	return (count);
}
