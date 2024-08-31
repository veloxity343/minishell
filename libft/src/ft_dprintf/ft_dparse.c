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

int	ft_format(int fd, char spec, va_list args, t_flags flags)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_print_char(fd, va_arg(args, int), flags);
	else if (spec == 's')
		count += ft_print_str(fd, va_arg(args, const char *), flags);
	else if (spec == 'p')
		count += ft_print_ptr(fd, (unsigned long int)va_arg(args, void *),
				flags);
	else if (spec == 'd' || spec == 'i')
		count += ft_print_int(fd, va_arg(args, int), flags);
	else if (spec == 'u')
		count += ft_print_unsigned(fd, va_arg(args, unsigned int), flags);
	else if (spec == 'x')
		count += ft_print_hex(fd, va_arg(args, unsigned int), 0, flags);
	else if (spec == 'X')
		count += ft_print_hex(fd, va_arg(args, unsigned int), 1, flags);
	else if (spec == '%')
		count += ft_print_char(fd, '%', flags);
	return (count);
}

int	ft_parse_flags(const char *str, int i, va_list args, t_flags *flags)
{
	while (str[++i] && ft_ismod(str[i]))
	{
		if (str[i] == '-')
			*flags = ft_flag_left(*flags);
		if (str[i] == '0' && flags->left == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = ft_flag_precision(str, i, args, flags);
		if (str[i] == '*')
			*flags = ft_flag_width(args, *flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (ft_isdigit(str[i]))
			*flags = ft_flag_digit(str[i], *flags);
		if (ft_isspec(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}

int	ft_parse(int fd, char *str, va_list args)
{
	int		i;
	int		count;
	t_flags	flags;

	i = -1;
	count = 0;
	while (str[++i])
	{
		flags = ft_flags_init();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i = ft_parse_flags(str, i, args, &flags);
			if (str[i] != '\0' && flags.spec > 0 && ft_isspec(str[i]))
				count += ft_format(fd, str[i], args, flags);
			else if (str[i] != '\0')
				count += ft_print_char(fd, str[i], flags);
		}
		else
			count += ft_putchar(fd, str[i]);
	}
	return (count);
}
