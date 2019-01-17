/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 12:14:12 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/12 12:14:21 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_printbits(char *str, t_format fx)
{
	char	*a;
	int		num;
	int		n;
	int		i;

	n = 0;
	i = !fx.mods ? 32 : 64;
	if (fx.mods == 'L')
		i = 80;
	i += i / 8 - 1;
	if (fx.precs >= 1 && fx.precs <= i)
		i = fx.precs;
	fx.precs = i;
	a = ft_strnew(i--);
	num = str[n];
	while (i >= 0)
	{
		a[i--] = num & 1 ? '1' : '0';
		num = num >> 1;
		if ((i == -1 || !((fx.precs - i) % 9)) && (num = str[++n]) != INT_MAX)
			a[i--] = ' ';
	}
	return (a);
}
