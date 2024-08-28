/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:52:28 by rcheong           #+#    #+#             */
/*   Updated: 2024/03/04 15:52:25 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (!haystack && !len)
		return (0);
	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *) haystack);
	while (*haystack && len)
	{
		if (*needle == *haystack)
		{
			i = 1;
			while ((len - i) && needle[i] \
					&& needle[i] == haystack[i])
				i++;
			if (i == needle_len)
				return ((char *) haystack);
		}
		haystack++;
		len--;
	}
	return (0);
}
