/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:49:43 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 13:22:30 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprint_intval(int fd, char *strint, int n, t_dflags flags)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (flags.zero == 0 || flags.precision >= 0)
			count += ft_dputchar(fd, '-');
	}
	else if (flags.plus == 1 && flags.zero == 0)
		count += ft_dputchar(fd, '+');
	else if (flags.space == 1 && flags.zero == 0)
		count += ft_dputchar(fd, ' ');
	if (flags.precision >= 0)
		count += ft_dpad_width(fd, flags.precision - 1, ft_strlen(strint) - 1,
				1);
	count += ft_dprint_safe_str(fd, strint);
	return (count);
}

int	ft_dprint_sign_flag(int fd, int n, t_dflags *flags)
{
	int	count;

	count = 0;
	if (n < 0 && flags->precision == -1)
	{
		count += ft_dputchar(fd, '-');
		flags->width--;
	}
	else if (flags->plus == 1)
		count += ft_dputchar(fd, '+');
	else if (flags->space == 1)
	{
		count += ft_dputchar(fd, ' ');
		flags->width--;
	}
	return (count);
}

int	ft_dpad_int(int fd, char *strint, int n, t_dflags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1)
		count += ft_dprint_sign_flag(fd, n, &flags);
	if (flags.left == 1)
		count += ft_dprint_intval(fd, strint, n, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(strint))
		flags.precision = ft_strlen(strint);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (n < 0 && flags.left == 0)
			flags.width -= 1;
		count += ft_dpad_width(fd, flags.width, 0, 0);
	}
	else
		count += ft_dpad_width(fd, flags.width - flags.plus - flags.space,
				ft_strlen(strint), flags.zero);
	if (flags.left == 0)
		count += ft_dprint_intval(fd, strint, n, flags);
	return (count);
}

int	ft_dprint_int(int fd, int n, t_dflags flags)
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
		count += ft_dpad_width(fd, flags.width, 0, 0);
		return (count);
	}
	strint = ft_ditoa_long(nb);
	if (!strint)
		return (0);
	count += ft_dpad_int(fd, strint, n, flags);
	free(strint);
	return (count);
}
