/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:31:36 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/11 12:42:02 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_print_safe_str(int fd, const char *str)
{
	int	len;

	if (str == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
	return (len);
}

int	ft_str_precision(int fd, const char *str, int precision)
{
	int	count;

	count = 0;
	while (str[count] && count < precision)
		write(fd, &str[count++], 1);
	return (count);
}

int	ft_pad_str(int fd, const char *str, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
	{
		count += ft_pad_width(fd, flags.precision, ft_strlen(str), 0);
		count += ft_str_precision(fd, str, flags.precision);
	}
	else
		count += ft_str_precision(fd, str, ft_strlen(str));
	return (count);
}

int	ft_print_str(int fd, const char *str, t_flags flags)
{
	int	count;

	count = 0;
	if (str == NULL)
		str = "(null)";
	if (flags.precision >= 0 && (size_t)flags.precision > ft_strlen(str))
		flags.precision = ft_strlen(str);
	if (flags.left == 1)
		count += ft_pad_str(fd, str, flags);
	if (flags.precision >= 0)
		count += ft_pad_width(fd, flags.width, flags.precision, 0);
	else
		count += ft_pad_width(fd, flags.width, ft_strlen(str), 0);
	if (flags.left == 0)
		count += ft_pad_str(fd, str, flags);
	return (count);
}
