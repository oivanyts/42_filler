/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:59:50 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 13:48:44 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_count_st(long long int n, int base)
{
	size_t	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		if (base == 10)
			count++;
	}
	while (n >= base)
	{
		n /= base;
		count++;
	}
	return (count);
}

char			*ft_itoa_base(int num, int base)
{
	char			*str;
	size_t			lenth;
	long long int	n;
	char			*a;

	a = "0123456789ABCDEF";
	n = (long long int)num;
	lenth = ft_count_st(n, base);
	if (!(str = (char *)malloc(sizeof(char) * lenth + 1)))
		return (NULL);
	if (n < 0)
	{
		if (base == 10)
			*str = '-';
		n *= -1;
	}
	str[lenth--] = '\0';
	while (n >= base)
	{
		str[lenth--] = a[n % base];
		n /= base;
	}
	str[lenth] = a[n];
	return (str);
}
