/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dparse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:30:05 by rcheong           #+#    #+#             */
/*   Updated: 2024/08/31 16:02:40 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dformat(int fd, char spec, va_list args, dt_flags flags)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_dprint_char(fd, va_arg(args, int), flags);
	else if (spec == 's')
		count += ft_dprint_str(fd, va_arg(args, const char *), flags);
	else if (spec == 'p')
		count += ft_dprint_ptr(fd, (unsigned long int)va_arg(args, void *),
				flags);
	else if (spec == 'd' || spec == 'i')
		count += ft_dprint_int(fd, va_arg(args, int), flags);
	else if (spec == 'u')
		count += ft_dprint_unsigned(fd, va_arg(args, unsigned int), flags);
	else if (spec == 'x')
		count += ft_dprint_hex(fd, va_arg(args, unsigned int), 0, flags);
	else if (spec == 'X')
		count += ft_dprint_hex(fd, va_arg(args, unsigned int), 1, flags);
	else if (spec == '%')
		count += ft_dprint_char(fd, '%', flags);
	return (count);
}

int	ft_dparse_flags(const char *str, int i, va_list args, dt_flags *flags)
{
	while (str[++i] && ft_dismod(str[i]))
	{
		if (str[i] == '-')
			*flags = ft_dflag_left(*flags);
		if (str[i] == '0' && flags->left == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = ft_dflag_precision(str, i, args, flags);
		if (str[i] == '*')
			*flags = ft_dflag_width(args, *flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (ft_isdigit(str[i]))
			*flags = ft_dflag_digit(str[i], *flags);
		if (ft_disspec(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}

int	ft_dparse(int fd, char *str, va_list args)
{
	int		i;
	int		count;
	dt_flags	flags;

	i = -1;
	count = 0;
	while (str[++i])
	{
		flags = ft_dflags_init();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i = ft_dparse_flags(str, i, args, &flags);
			if (str[i] != '\0' && flags.spec > 0 && ft_disspec(str[i]))
				count += ft_dformat(fd, str[i], args, flags);
			else if (str[i] != '\0')
				count += ft_dprint_char(fd, str[i], flags);
		}
		else
			count += ft_dputchar(fd, str[i]);
	}
	return (count);
}
