/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dismod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:30:22 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/08 15:47:43 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_disspec(int c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}

int	ft_disflag(int c)
{
	if (c == '-' || c == '0' || c == '.' || c == '*' || c == '#' || c == ' '
		|| c == '+')
		return (1);
	return (0);
}

int	ft_dismod(int c)
{
	return (ft_disspec(c) || ft_isdigit(c) || ft_disflag(c));
}
