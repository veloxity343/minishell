/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:41:18 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 13:22:29 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprint_xprefix(int fd, int is_upper)
{
	if (is_upper == 1)
		ft_dprint_safe_str(fd, "0X");
	else
		ft_dprint_safe_str(fd, "0x");
	return (2);
}

int	ft_dprint_xvalue(t_xprint_args args)
{
	int	count;

	count = 0;
	if (args.flags.zero == 0 && args.flags.hash == 1 && args.n != 0)
		count += ft_dprint_xprefix(args.fd, args.is_upper);
	if (args.flags.precision >= 0)
		count += ft_dpad_width(args.fd, args.flags.precision - 1,
				ft_strlen(args.strint) - 1, 1);
	count += ft_dprint_safe_str(args.fd, args.strint);
	return (count);
}

int	ft_dprint_xformat(t_xprint_args args)
{
	int	count;

	count = 0;
	if (args.flags.zero == 1 && args.flags.hash == 1 && args.n != 0)
		count += ft_dprint_xprefix(args.fd, args.is_upper);
	if (args.flags.left == 1)
		count += ft_dprint_xvalue(args);
	if (args.flags.precision >= 0
		&& (size_t)args.flags.precision < ft_strlen(args.strint))
		args.flags.precision = ft_strlen(args.strint);
	if (args.flags.precision >= 0)
	{
		args.flags.width -= args.flags.precision;
		count += ft_dpad_width(args.fd, args.flags.width, 0, 0);
	}
	else
		count += ft_dpad_width(args.fd, args.flags.width, ft_strlen(args.strint)
				+ (args.flags.hash * 2), args.flags.zero);
	if (args.flags.left == 0)
		count += ft_dprint_xvalue(args);
	return (count);
}

int	ft_dprint_hex(int fd, unsigned int n, int is_upper, t_dflags flags)
{
	char			*strint;
	int				count;
	t_xprint_args	args;

	count = 0;
	if (flags.precision == 0 && n == 0)
		return (ft_dpad_width(fd, flags.width, 0, 0));
	strint = ft_dprintf_xtoa(n, is_upper);
	if (!strint)
		return (0);
	args = (t_xprint_args){fd, strint, n, is_upper, flags};
	count = ft_dprint_xformat(args);
	free(strint);
	return (count);
}
