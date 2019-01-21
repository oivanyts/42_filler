/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:32:09 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/06 12:39:48 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int				count_dig(long double num, t_format fx)
{
	int count;

	if ((count = 1) && num < 0.0)
		num *= -1.0;
	if (num >= 1.0)
	{
		while (num > 1.0 && num >= 10.0)
		{
			num /= 10.0;
			count++;
		}
		if (fx.type == 'e')
			count--;
	}
	else if (fx.type == 'e' && num)
	{
		if ((count = -1) && num == 0.)
			return (count);
		while (num <= 0.1 && num > 0.0)
		{
			num *= 10.0;
			count--;
		}
	}
	return (count);
}

static long double		str_to_dot(long double num, char *str, int len,
		int prec)
{
	size_t		n;
	char		dig;
	long double	e;

	n = 0;
	e = ft_exp(10, len - 1);
	if (str[n] == '-')
		n++;
	while (len--)
	{
		dig = (char)(((num) / e));
		str[n++] = (char)(dig + '0');
		num -= (long double)dig * e;
		e /= 10.0;
	}
	if (prec)
		str[n] = '.';
	return (num);
}

static void				str_end(long double num, char *str, int prec,
		int esize)
{
	size_t		n;
	char		dig;
	long double	e;

	n = 0;
	e = 0.1;
	while (prec--)
	{
		dig = (char)(ft_round_double(num, 20) / e);
		str[n++] = (char)(dig + '0');
		num -= (long double)dig * e;
		e /= 10.0;
	}
	if (esize > INT_MIN)
	{
		str[n++] = 'e';
		str[n++] = (char)(esize >= 0 ? '+' : '-');
		esize *= esize < 0 ? -1 : 1;
		prec = (int)(esize < 100 ? 101 : ft_exp(10, ft_num_size(esize)) + 1);
		while (prec /= 10)
		{
			str[n++] = (char)(esize / prec + '0');
			esize %= prec;
		}
	}
}

static int				str_ready(char **str, t_format fx, int len)
{
	char empty;

	empty = fx.flag[3] == '0' && fx.flag[0] != '-' ? '0' : ' ';
	if (fx.whidth > len)
	{
		*str = ft_strnew((size_t)fx.whidth);
		ft_memset(*str, empty, (size_t)fx.whidth);
	}
	else
	{
		*str = ft_strnew(len);
		return (0);
	}
	return (fx.whidth - len - (fx.type == 'e') * 3);
}

char					*ft_itoa_double(long double num, t_format fx)
{
	char	*str;
	int		len;
	size_t	n;

	if ((len = count_dig(num, fx)) > INT_MIN && fx.precs < 0)
		fx.precs = 6;
	n = (size_t)str_ready(&str, fx, ((fx.type == 'f' ? len + fx.precs + 1 :
	fx.precs + 2 + ft_num_size(len)) + ((num < 0.) || fx.flag[1] == '+')));
	if (fx.flag[0] == '-')
		n = 0;
	if (fx.flag[2] == ' ' && ((fx.flag[0] == '-' && num > 0. && n++) ||
							  fx.flag[3] == '0'))
		str[0] = ' ';
	if (num < 0.0 && (num *= -1))
		fx.flag[1] = '-';
	while (num && fx.type != 'f' && (num < 1 || num > 10.0))
		num > 10.0 ? (num /= 10) : (num *= 10);
	num = ft_round_double(num, fx.precs);
	if (fx.flag[1] == '+' || fx.flag[1] == '-')
		str[(fx.flag[3] == '0' && n++ ? 0 : (n++))] = fx.flag[1];
	num = str_to_dot(num, &str[n], (len - 1) * (fx.type == 'f') + 1, fx.precs);
	str_end(num, &str[len * (fx.type != 'e') + (fx.precs > 0) + (fx.type == 'e')
	+ n], fx.precs, INT_MIN * (fx.type != 'e') + (len) * (fx.type == 'e'));
	return (str);
}

