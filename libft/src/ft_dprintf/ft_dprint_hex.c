/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:41:18 by rcheong           #+#    #+#             */
/*   Updated: 2024/08/31 16:10:27 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_print_xprefix(int fd, int is_upper)
{
	if (is_upper == 1)
		ft_print_safe_str(fd, "0X");
	else
		ft_print_safe_str(fd, "0x");
	return (2);
}

int	ft_print_xvalue(t_xprint_args args)
{
	int	count;

	count = 0;
	if (args.flags.zero == 0 && args.flags.hash == 1 && args.n != 0)
		count += ft_print_xprefix(args.fd, args.is_upper);
	if (args.flags.precision >= 0)
		count += ft_pad_width(args.fd, args.flags.precision - 1,
				ft_strlen(args.strint) - 1, 1);
	count += ft_print_safe_str(args.fd, args.strint);
	return (count);
}

int	ft_print_xformat(t_xprint_args args)
{
	int	count;

	count = 0;
	if (args.flags.zero == 1 && args.flags.hash == 1 && args.n != 0)
		count += ft_print_xprefix(args.fd, args.is_upper);
	if (args.flags.left == 1)
		count += ft_print_xvalue(args);
	if (args.flags.precision >= 0
		&& (size_t)args.flags.precision < ft_strlen(args.strint))
		args.flags.precision = ft_strlen(args.strint);
	if (args.flags.precision >= 0)
	{
		args.flags.width -= args.flags.precision;
		count += ft_pad_width(args.fd, args.flags.width, 0, 0);
	}
	else
		count += ft_pad_width(args.fd, args.flags.width, ft_strlen(args.strint)
				+ (args.flags.hash * 2), args.flags.zero);
	if (args.flags.left == 0)
		count += ft_print_xvalue(args);
	return (count);
}

int	ft_print_hex(int fd, unsigned int n, int is_upper, t_flags flags)
{
	char			*strint;
	int				count;
	t_xprint_args	args;

	count = 0;
	if (flags.precision == 0 && n == 0)
		return (ft_pad_width(fd, flags.width, 0, 0));
	strint = ft_printf_xtoa(n, is_upper);
	if (!strint)
		return (0);
	args = (t_xprint_args){fd, strint, n, is_upper, flags};
	count = ft_print_xformat(args);
	free(strint);
	return (count);
}

/* int	ft_print_xvalue(int fd, char *strint, int n, int is_upper,
		t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 0 && flags.hash == 1 && n != 0)
		count += ft_print_xprefix(fd, is_upper);
	if (flags.precision >= 0)
		count += ft_pad_width(fd, flags.precision - 1,
				ft_strlen(strint) - 1, 1);
	count += ft_print_safe_str(fd, strint);
	return (count);
}

int	ft_print_xformat(int fd, char *strint, int n, int is_upper, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1 && flags.hash == 1 && n != 0)
		count += ft_print_xprefix(fd, is_upper);
	if (flags.left == 1)
		count += ft_print_xvalue(fd, strint, n, is_upper, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(strint))
		flags.precision = ft_strlen(strint);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += ft_pad_width(fd, flags.width, 0, 0);
	}
	else
		count += ft_pad_width(fd, flags.width,
				ft_strlen(strint) + (flags.hash * 2), flags.zero);
	if (flags.left == 0)
		count += ft_print_xvalue(fd, strint, n, is_upper, flags);
	return (count);
}

int	ft_print_hex(int fd, unsigned int n, int is_upper, t_flags flags)
{
	char	*strint;
	int		count;

	count = 0;
	if (flags.precision == 0 && n == 0)
	{
		count += ft_pad_width(fd, flags.width, 0, 0);
		return (count);
	}
	strint = ft_printf_xtoa(n, is_upper);
	if (!strint)
		return (0);
	count += ft_print_xformat(fd, strint, n, is_upper, flags);
	free(strint);
	return (count);
} */
