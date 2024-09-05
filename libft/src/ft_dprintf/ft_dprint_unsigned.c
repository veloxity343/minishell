/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:12:04 by rcheong           #+#    #+#             */
/*   Updated: 2024/08/31 16:03:02 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dunsigned_str(int fd, char *strint, dt_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
		count += ft_dpad_width(fd, flags.precision - 1, ft_strlen(strint) - 1,
				1);
	count += ft_dprint_safe_str(fd, strint);
	return (count);
}

int	ft_dpad_unsigned(int fd, char *strint, dt_flags flags)
{
	int	count;

	count = 0;
	if (flags.left == 1)
		count += ft_dunsigned_str(fd, strint, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(strint))
		flags.precision = ft_strlen(strint);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += ft_dpad_width(fd, flags.width, 0, 0);
	}
	else
		count += ft_dpad_width(fd, flags.width, ft_strlen(strint), flags.zero);
	if (flags.left == 0)
		count += ft_dunsigned_str(fd, strint, flags);
	return (count);
}

int	ft_dprint_unsigned(int fd, unsigned n, dt_flags flags)
{
	char	*strint;
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (flags.precision == 0 && n == 0)
	{
		count += ft_dpad_width(fd, flags.width, 0, 0);
		return (count);
	}
	strint = ft_ditoa_long(nb);
	if (!strint)
		return (0);
	count += ft_dpad_unsigned(fd, strint, flags);
	free(strint);
	return (count);
}
