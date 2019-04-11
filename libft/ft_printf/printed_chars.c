/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printed_chars.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 15:58:28 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:45 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		printed_chars(t_fmt fmt, long long num)
{
	int	ilen;

	ilen = pf_longlen(num);
	if (num < 0)
		ilen++;
	if (fmt.prec == 0 && num == 0)
		ilen = 0;
	if (fmt.prec > ilen || fmt.width > ilen)
	{
		if (fmt.prec > fmt.width && num >= 0)
			ilen = fmt.prec;
		else if (fmt.prec >= fmt.width && num < 0)
			ilen = fmt.prec + 1;
		else
			ilen = fmt.width;
	}
	if (fmt.width <= pf_longlen(num) &&
	num >= 0 && (fmt.SPACE || fmt.PLUS))
		ilen++;
	return (ilen);
}
