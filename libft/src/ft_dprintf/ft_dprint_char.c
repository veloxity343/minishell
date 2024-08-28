/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:31:28 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/25 11:29:53 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_putchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_pad_width(int fd, int width, int size, int zero)
{
	int	count;

	count = 0;
	while (width - size > 0)
	{
		if (zero)
			count += ft_putchar(fd, '0');
		else
			count += ft_putchar(fd, ' ');
		width--;
	}
	return (count);
}

int	ft_print_char(int fd, int c, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.left == 1)
	{
		if (c == '\0')
			count += ft_putchar(fd, '\0');
		else
			count += ft_putchar(fd, c);
	}
	count += ft_pad_width(fd, flags.width, 1, flags.zero);
	if (flags.left == 0)
	{
		if (c == '\0')
			count += ft_putchar(fd, '\0');
		else
			count += ft_putchar(fd, c);
	}
	return (count);
}
