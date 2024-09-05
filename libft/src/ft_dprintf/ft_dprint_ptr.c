/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:31:33 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/08 15:47:15 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dptrhex_len(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void	ft_dprint_addr(int fd, unsigned long int n)
{
	if (n >= 16)
	{
		ft_dprint_addr(fd, n / 16);
		ft_dprint_addr(fd, n % 16);
	}
	else
	{
		if (n < 10)
			ft_dputchar(fd, n + '0');
		else if (n >= 10)
			ft_dputchar(fd, (n - 10) + 'a');
	}
}

int	ft_dprint_pvalue(int fd, unsigned long int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count += ft_dprint_safe_str(fd, "0x0");
		return (count);
	}
	count += ft_dprint_safe_str(fd, "0x");
	ft_dprint_addr(fd, n);
	count += ft_dptrhex_len(n);
	return (count);
}

int	ft_dprint_ptr(int fd, unsigned long int n, dt_flags flags)
{
	int	count;

	count = 0;
	if (n == 0)
		flags.width -= ft_strlen("0x0") - 1;
	else
		flags.width -= 2;
	if (flags.left == 1)
		count += ft_dprint_pvalue(fd, n);
	count += ft_dpad_width(fd, flags.width, ft_dptrhex_len(n), 0);
	if (flags.left == 0)
		count += ft_dprint_pvalue(fd, n);
	return (count);
}
