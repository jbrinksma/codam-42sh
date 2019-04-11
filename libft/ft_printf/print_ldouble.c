/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_ldouble.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 15:52:49 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:52:59 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					print_ldouble(t_fmt fmt, long double num)
{
	long long	n;
	long long	ex;
	int			ret;
	int			neg;
	t_fmt		copy;

	ret = check_special(fmt, num);
	neg = is_negzero(num);
	if (ret != 0)
		return (ret);
	n = (long long)num;
	num = (long double)n - num;
	if (fmt.prec == -1)
		fmt.prec = 6;
	copy = copy_fmt(fmt);
	fmt = prepare_fmt_num(fmt, copy, neg);
	if (copy.prec == 0)
		n = round_num(n, num);
	ret += print_signed(fmt, n);
	ret += print_dot(copy);
	ex = round_expo(num, copy.prec);
	fmt = prepare_fmt_exp(fmt, copy, ret);
	if (fmt.prec != 0 || (fmt.MIN && fmt.width > 0))
		ret += print_signed(fmt, ex);
	return (ret);
}
