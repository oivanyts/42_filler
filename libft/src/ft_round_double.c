/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:31:57 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/14 17:32:00 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

long double		ft_round_double(long double num, int precision)
{
	long double e;
	int			pos;

	pos = num < 0.0 && (num *= -1) ? -1 : 1;
	e = ft_exp(10, precision + 1);
	if ((long long int)((num * e)) % 10 >= 5)
		return ((num + (1.0 / (e / 10.0))) * pos);
	return (num * pos);
}
