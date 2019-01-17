/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnum_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:59:50 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 13:48:44 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static size_t	ft_count_st(unsigned long long int n, int base, t_format fx)
{
	size_t	count;

	count = 1;
	if (fx.type == 'p' && !n && fx.precs > INT_MIN)
		count = 0;
	else if (!n && fx.precs > INT_MIN && (fx.flag[4] != '#' || base == 16))
		return (0);
	else if (!n && fx.flag[4] == '#' && base == 8)
		return (1);
	if ((fx.flag[4] == '#' && n && base != 10) || fx.type == 'p')
		count += base / 8;
	while (n >= (unsigned int)base)
	{
		n /= base;
		count++;
	}
	return (count);
}

static void		f_addpref(char *str, int base)
{
	char	*to_add;

	to_add = ft_strchr(str, '0');
	if (base == 8)
		*to_add = '0';
	if (base == 16)
		*++to_add = 'X';
}

static size_t	str_ready(char *str, t_format fx, size_t len, int base)
{
	size_t	full_len;
	size_t	end_num;

	if ((fx.precs > 2) && ((fx.flag[4] == '#' && base == 16) ||
	(fx.type == 'p')))
		fx.precs += 2;
	full_len = (size_t)ft_max_number(fx.whidth, fx.precs, (int)len);
	if (fx.precs < (int)len && fx.precs > 1)
		fx.precs = (int)len;
	else if (fx.precs > 1)
		len = (size_t)fx.precs;
	end_num = fx.flag[0] == '-' && (int)full_len != fx.precs ? len : full_len;
	if (fx.precs >= (int)len)
		len = (size_t)fx.precs;
	if ((fx.flag[3] != '0' || fx.flag[0] == '-' ||
	fx.precs > INT_MIN) && fx.whidth)
	{
		ft_memset(str, ' ', full_len);
		ft_memset(&str[end_num - len], '0', len);
	}
	else if (fx.whidth)
		ft_memset(str, '0', full_len);
	if (!fx.whidth)
		ft_memset(&str[end_num - len], '0', len);
	return (end_num);
}

char			*ft_strnum_base(unsigned long long int n, int base, t_format fx)
{
	char	*ret;
	char	*temp;
	size_t	num_size;
	size_t	str_size;
	size_t	i;

	temp = "0123456789ABCDEF";
	num_size = ft_count_st(n, base, fx);
	str_size = (size_t)ft_max_number((int)num_size, fx.whidth, fx.precs);
	if ((fx.flag[4] == '#' && n) || fx.type == 'p')
		str_size += base / 8;
	ret = ft_strnew(str_size);
	i = str_ready(ret, fx, num_size, base);
	if ((fx.flag[4] == '#' && n) || fx.type == 'p')
		f_addpref(ret, base);
	if (!n && !fx.precs)
		return (ret);
	while (n >= (unsigned int)base)
	{
		ret[--i] = temp[n % base];
		n /= base;
	}
	ret[--i] = temp[n];
	return (ret);
}
