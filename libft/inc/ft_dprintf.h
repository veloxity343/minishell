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

typedef struct ds_flags
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
}			dt_flags;

typedef struct s_xprint_args
{
	int		fd;
	char	*strint;
	int		n;
	int		is_upper;
	dt_flags	flags;
}			t_xprint_args;

dt_flags		ft_dflags_init(void);
dt_flags		ft_dflag_left(dt_flags flags);
dt_flags		ft_dflag_digit(char c, dt_flags flags);
dt_flags		ft_dflag_width(va_list args, dt_flags flags);
int			ft_dflag_precision(const char *str, int i, va_list args,
				dt_flags *flags);
int			ft_dpad_width(int fd, int width, int size, int zero);

/* ---------- SPECS ---------- */

// c
int			ft_dprint_char(int fd, int c, dt_flags flags);
int			ft_dputchar(int fd, int c);
// s
int			ft_dprint_str(int fd, const char *str, dt_flags flags);
int			ft_dpad_str(int fd, const char *str, dt_flags flags);
int			ft_dstr_precision(int fd, const char *str, int precision);
int			ft_dprint_safe_str(int fd, const char *str);
// p
int			ft_dprint_ptr(int fd, unsigned long int n, dt_flags flags);
int			ft_dprint_pvalue(int fd, unsigned long int n);
void		ft_dprint_addr(int fd, unsigned long int n);
// d, i
int			ft_dprint_int(int fd, int n, dt_flags flags);
int			ft_dpad_int(int fd, char *strint, int n, dt_flags flags);
int			ft_dprint_sign_flag(int fd, int n, dt_flags *flags);
int			ft_dprint_intval(int fd, char *strint, int n, dt_flags flags);
// u
int			ft_dprint_unsigned(int fd, unsigned n, dt_flags flags);
int			ft_dpad_unsigned(int fd, char *strint, dt_flags flags);
int			ft_dunsigned_str(int fd, char *strint, dt_flags flags);
// x, X
int			ft_dprint_hex(int fd, unsigned int n, int is_upper, dt_flags flags);
int			ft_dprint_xformat(t_xprint_args args);
int			ft_dprint_xvalue(t_xprint_args args);
int			ft_dprint_xprefix(int fd, int is_upper);

/* ---------- HELPERS ---------- */

int			ft_dismod(int c);
int			ft_disflag(int c);
int			ft_disspec(int c);
int			ft_dptrhex_len(unsigned long int n);
char		*ft_ditoa_long(long n);
char		*ft_dprintf_xtoa(unsigned long int n, int is_upper);

/* ---------- PRINTF ---------- */

int			ft_dprintf(int fd, const char *format, ...);
int			ft_dparse(int fd, char *str, va_list args);
int			ft_dparse_flags(const char *str, int i, va_list args,
				dt_flags *flags);
int			ft_dformat(int fd, char type, va_list args, dt_flags flags);

#endif