/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_prntf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:32:09 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/06 12:39:48 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static size_t	ft_count_st(long long int num, t_format *fx)
{
	size_t					count;
	unsigned long long int	n;

	count = !fx->precs && !num ? 0 : 1;
	if ((num < 0 || fx->flag[1] == '+' || fx->flag[2] == ' ')
	&& fx->type != 'u')
	{
		count++;
		fx->flag[2] != ' ' ? (fx->flag[1] = '+') :
		(fx->flag[2] = ' ');
	}
	n = (unsigned long long int)(num < 0 ? num * (-1) : num);
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static size_t	str_ready(char *str, t_format fx, size_t len)
{
	size_t	full_len;
	size_t	end_of_num;

	if ((fx.flag[2] == ' ' || fx.flag[1] == '+') && fx.precs > INT_MIN)
		fx.precs++;
	full_len = (size_t)ft_max_number(fx.whidth, fx.precs, len);
	if (fx.precs < (int)len && fx.precs > 1)
		fx.precs = (int)len;
	else if (fx.precs > 1)
		len = (size_t)fx.precs;
	if (fx.flag[0] == '-')
		end_of_num = full_len != (size_t)fx.precs ? len : full_len;
	else
		end_of_num = full_len;
	if ((fx.flag[3] != '0' || fx.flag[0] == '-' || fx.precs >= 0) && fx.whidth)
	{
		ft_memset(str, ' ', full_len);
		ft_memset(&str[end_of_num - len], '0', len);
	}
	else if (fx.whidth)
		ft_memset(str, '0', full_len);
	else
		ft_memset(&str[end_of_num - len], '0', len);
	return (end_of_num);
}

static void		f_addpref(char *str, long long int num, t_format fx)
{
	char	add;
	char	*to_add;

	to_add = ft_strchr(str, '0');
	add = 0;
	if (num < 0)
		add = '-';
	else if (fx.flag[1] == '+')
		add = '+';
	else if (fx.flag[2] == ' ')
		add = ' ';
	if (add)
		*to_add = add;
}

char			*ft_itoa_prntf(long long int num, t_format fx)
{
	char					*str;
	size_t					lenth_num;
	size_t					len;
	size_t					i;
	unsigned long long int	n;

	lenth_num = ft_count_st(num, &fx);
	len = (size_t)ft_max_number((int)lenth_num, fx.whidth, fx.precs);
	str = ft_strnew(len);
	i = str_ready(str, fx, lenth_num);
	f_addpref(str, num, fx);
	if (!num && !fx.precs)
	{
		if (len > 1)
			ft_memset(str, ' ', len);
		return (str);
	}
	n = (unsigned long long int)(num < 0 ? num * (-1) : num);
	while (n >= 10)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	str[--i] = n + '0';
	return (str);
}
