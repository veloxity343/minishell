/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:49:43 by rcheong           #+#    #+#             */
/*   Updated: 2024/08/31 16:02:54 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_print_intval(int fd, char *strint, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (flags.zero == 0 || flags.precision >= 0)
			count += ft_putchar(fd, '-');
	}
	else if (flags.plus == 1 && flags.zero == 0)
		count += ft_putchar(fd, '+');
	else if (flags.space == 1 && flags.zero == 0)
		count += ft_putchar(fd, ' ');
	if (flags.precision >= 0)
		count += ft_pad_width(fd, flags.precision - 1, ft_strlen(strint) - 1,
				1);
	count += ft_print_safe_str(fd, strint);
	return (count);
}

int	ft_print_sign_flag(int fd, int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (n < 0 && flags->precision == -1)
	{
		count += ft_putchar(fd, '-');
		flags->width--;
	}
	else if (flags->plus == 1)
		count += ft_putchar(fd, '+');
	else if (flags->space == 1)
	{
		count += ft_putchar(fd, ' ');
		flags->width--;
	}
	return (count);
}

int	ft_pad_int(int fd, char *strint, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1)
		count += ft_print_sign_flag(fd, n, &flags);
	if (flags.left == 1)
		count += ft_print_intval(fd, strint, n, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(strint))
		flags.precision = ft_strlen(strint);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (n < 0 && flags.left == 0)
			flags.width -= 1;
		count += ft_pad_width(fd, flags.width, 0, 0);
	}
	else
		count += ft_pad_width(fd, flags.width - flags.plus - flags.space,
				ft_strlen(strint), flags.zero);
	if (flags.left == 0)
		count += ft_print_intval(fd, strint, n, flags);
	return (count);
}

int	ft_print_int(int fd, int n, t_flags flags)
{
	char	*strint;
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		if (flags.zero == 0)
			flags.width--;
	}
	if (flags.precision == 0 && n == 0)
	{
		count += ft_pad_width(fd, flags.width, 0, 0);
		return (count);
	}
	strint = ft_itoa_long(nb);
	if (!strint)
		return (0);
	count += ft_pad_int(fd, strint, n, flags);
	free(strint);
	return (count);
}
