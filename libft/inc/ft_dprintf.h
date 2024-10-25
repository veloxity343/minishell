/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheong <rcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:53:36 by rcheong           #+#    #+#             */
/*   Updated: 2024/10/21 13:22:01 by rcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"
# include <stdarg.h>

/* ---------- FLAGS ---------- */

typedef struct s_dflags
{
	int			spec;
	int			left;
	int			zero;
	int			precision;
	int			width;
	int			star;
	int			hash;
	int			space;
	int			plus;
}				t_dflags;

typedef struct s_xprint_args
{
	int			fd;
	char		*strint;
	int			n;
	int			is_upper;
	t_dflags	flags;
}				t_xprint_args;

t_dflags		ft_dflags_init(void);
t_dflags		ft_dflag_left(t_dflags flags);
t_dflags		ft_dflag_digit(char c, t_dflags flags);
t_dflags		ft_dflag_width(va_list args, t_dflags flags);
int				ft_dflag_precision(const char *str, int i, va_list args,
					t_dflags *flags);
int				ft_dpad_width(int fd, int width, int size, int zero);

/* ---------- SPECS ---------- */

// c
int				ft_dprint_char(int fd, int c, t_dflags flags);
int				ft_dputchar(int fd, int c);
// s
int				ft_dprint_str(int fd, const char *str, t_dflags flags);
int				ft_dpad_str(int fd, const char *str, t_dflags flags);
int				ft_dstr_precision(int fd, const char *str, int precision);
int				ft_dprint_safe_str(int fd, const char *str);
// p
int				ft_dprint_ptr(int fd, unsigned long int n, t_dflags flags);
int				ft_dprint_pvalue(int fd, unsigned long int n);
void			ft_dprint_addr(int fd, unsigned long int n);
// d, i
int				ft_dprint_int(int fd, int n, t_dflags flags);
int				ft_dpad_int(int fd, char *strint, int n, t_dflags flags);
int				ft_dprint_sign_flag(int fd, int n, t_dflags *flags);
int				ft_dprint_intval(int fd, char *strint, int n, t_dflags flags);
// u
int				ft_dprint_unsigned(int fd, unsigned n, t_dflags flags);
int				ft_dpad_unsigned(int fd, char *strint, t_dflags flags);
int				ft_dunsigned_str(int fd, char *strint, t_dflags flags);
// x, X
int				ft_dprint_hex(int fd, unsigned int n, int is_upper,
					t_dflags flags);
int				ft_dprint_xformat(t_xprint_args args);
int				ft_dprint_xvalue(t_xprint_args args);
int				ft_dprint_xprefix(int fd, int is_upper);

/* ---------- HELPERS ---------- */

int				ft_dismod(int c);
int				ft_disflag(int c);
int				ft_disspec(int c);
int				ft_dptrhex_len(unsigned long int n);
char			*ft_ditoa_long(long n);
char			*ft_dprintf_xtoa(unsigned long int n, int is_upper);

/* ---------- PRINTF ---------- */

int				ft_dprintf(int fd, const char *format, ...);
int				ft_dparse(int fd, char *str, va_list args);
int				ft_dparse_flags(const char *str, int i, va_list args,
					t_dflags *flags);
int				ft_dformat(int fd, char type, va_list args, t_dflags flags);

#endif