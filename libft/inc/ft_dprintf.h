/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:53:36 by rcheong           #+#    #+#             */
/*   Updated: 2024/08/31 16:11:07 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"
# include <stdarg.h>

/* ---------- FLAGS ---------- */

typedef struct s_flags
{
	int		spec;
	int		left;
	int		zero;
	int		precision;
	int		width;
	int		star;
	int		hash;
	int		space;
	int		plus;
}			t_flags;

typedef struct s_xprint_args
{
	int		fd;
	char	*strint;
	int		n;
	int		is_upper;
	t_flags	flags;
}			t_xprint_args;

t_flags		ft_flags_init(void);
t_flags		ft_flag_left(t_flags flags);
t_flags		ft_flag_digit(char c, t_flags flags);
t_flags		ft_flag_width(va_list args, t_flags flags);
int			ft_flag_precision(const char *str, int i, va_list args,
				t_flags *flags);
int			ft_pad_width(int fd, int width, int size, int zero);

/* ---------- SPECS ---------- */

// c
int			ft_print_char(int fd, int c, t_flags flags);
int			ft_putchar(int fd, int c);
// s
int			ft_print_str(int fd, const char *str, t_flags flags);
int			ft_pad_str(int fd, const char *str, t_flags flags);
int			ft_str_precision(int fd, const char *str, int precision);
int			ft_print_safe_str(int fd, const char *str);
// p
int			ft_print_ptr(int fd, unsigned long int n, t_flags flags);
int			ft_print_pvalue(int fd, unsigned long int n);
void		ft_print_addr(int fd, unsigned long int n);
// d, i
int			ft_print_int(int fd, int n, t_flags flags);
int			ft_pad_int(int fd, char *strint, int n, t_flags flags);
int			ft_print_sign_flag(int fd, int n, t_flags *flags);
int			ft_print_intval(int fd, char *strint, int n, t_flags flags);
// u
int			ft_print_unsigned(int fd, unsigned n, t_flags flags);
int			ft_pad_unsigned(int fd, char *strint, t_flags flags);
int			ft_unsigned_str(int fd, char *strint, t_flags flags);
// x, X
int			ft_print_hex(int fd, unsigned int n, int is_upper, t_flags flags);
int			ft_print_xformat(t_xprint_args args);
int			ft_print_xvalue(t_xprint_args args);
int			ft_print_xprefix(int fd, int is_upper);

/* ---------- HELPERS ---------- */

int			ft_ismod(int c);
int			ft_isflag(int c);
int			ft_isspec(int c);
int			ft_ptrhex_len(unsigned long int n);
char		*ft_itoa_long(long n);
char		*ft_printf_xtoa(unsigned long int n, int is_upper);

/* ---------- PRINTF ---------- */

int			ft_dprintf(int fd, const char *format, ...);
int			ft_parse(int fd, char *str, va_list args);
int			ft_parse_flags(const char *str, int i, va_list args,
				t_flags *flags);
int			ft_format(int fd, char type, va_list args, t_flags flags);

#endif