/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/05 07:43:01 by omulder        #+#    #+#                */
/*   Updated: 2019/07/23 14:50:26 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define HASH	opt[0]
# define ZERO	opt[1]
# define MIN	opt[2]
# define SPACE	opt[3]
# define PLUS	opt[4]
# define APST	opt[5]

typedef struct	s_fmt
{
	int		fd;
	int		opt[6];
	int		width;
	int		prec;
	int		length;
	char	conv;
}				t_fmt;

int				ft_eprintf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				pf_isalpha(int c);
int				pf_isdigit(int c);
int				pf_atoi(const char *str);
int				pf_putchar(int fd, int c);
int				pf_putchar_uni(int fd, unsigned int c);
size_t			pf_strlen(const char *s);
void			pf_putstr(int fd, char const *s);
void			pf_putnstr(int fd, char const *s, size_t len);
int				pf_isspace(int c);
size_t			pf_charsize(unsigned int c);
int				check_special(t_fmt fmt, double num);
int				find_base(t_fmt fmt);
int				find_case(t_fmt fmt);
int				pf_isupper(char c);
int				pf_longlen(long long n);
int				ft_printf(const char *format, ...);
int				pf_ulonglen(unsigned long long n, int base);
int				is_char(t_fmt fmt);
int				is_charp(t_fmt fmt);
int				is_charsign(t_fmt fmt);
int				is_conversion(char c);
int				is_double(t_fmt fmt);
int				is_flag(char c);
int				is_hex(t_fmt fmt);
int				is_int(t_fmt fmt);
int				is_ldouble(t_fmt fmt);
int				is_length(char c);
int				is_long(t_fmt fmt);
int				is_longint(t_fmt fmt);
int				is_negzero(double num);
int				is_octal(t_fmt fmt);
int				is_option(char c);
int				is_short(t_fmt fmt);
int				is_signed(t_fmt fmt);
int				is_uchar(t_fmt fmt);
int				is_uint(t_fmt fmt);
int				is_ulong(t_fmt fmt);
int				is_unsigned(t_fmt fmt);
int				is_ushort(t_fmt fmt);
int				is_voidp(t_fmt fmt);
int				is_wcharp(t_fmt fmt);
int				print_dot(t_fmt copy);
int				print_char(t_fmt fmt, unsigned int c);
int				print_charp(t_fmt fmt, char *str);
int				print_double(t_fmt fmt, double num);
int				print_padding(int fd, char c, int size);
int				print_prehex(t_fmt fmt);
int				print_signed(t_fmt fmt, long long num);
int				print_unsigned(t_fmt fmt, unsigned long long num);
int				print_var(t_fmt fmt, va_list ap);
int				print_wcharp(t_fmt fmt, wchar_t *str);
int				print_wcharp(t_fmt fmt, wchar_t *str);
int				printed_chars(t_fmt fmt, long long num);
int				printed_uchars(t_fmt fmt, unsigned long long num);
int				print_ldouble(t_fmt fmt, long double num);
long double		pf_powl(long double x, long double y);
long long		pf_abs(long long n);
long long		round_expo(double expo, int prec);
long long		round_num(long long num, double expo);
size_t			pf_wstrlen(const wchar_t *s, int prec);
t_fmt			check_format(t_fmt fmt, const char **format, va_list ap);
t_fmt			copy_fmt(t_fmt fmt);
t_fmt			find_conversion(const char **format, t_fmt fmt);
t_fmt			find_length(const char **format, t_fmt fmt);
t_fmt			find_options(const char **format, t_fmt fmt);
t_fmt			find_precision(const char **format, t_fmt fmt, va_list ap);
t_fmt			find_width(const char **format, t_fmt fmt, va_list ap);
t_fmt			prepare_fmt_exp(t_fmt fmt, t_fmt copy, int ret);
t_fmt			prepare_fmt_num(t_fmt fmt, t_fmt copy, int neg);
t_fmt			reset_fmt(t_fmt fmt);
void			pf_putcharsign(int fd, long long c);
void			pf_putlong_base(int fd, long long n, int base, int up);
void			pf_putlong(int fd, long long n);
void			pf_putnwstr(int fd, wchar_t const *s, size_t len);
void			pf_putulong_base(int fd, unsigned long long n, int base,
int up);
void			pf_putwstr(int fd, wchar_t const *s);
void			put_backpadding(t_fmt fmt, long long num, int ilen);
void			put_paddingandsign(t_fmt fmt, long long num, int ilen);
void			put_upaddingandsign(t_fmt fmt, unsigned long long num, int ilen,
				int op);

#endif
