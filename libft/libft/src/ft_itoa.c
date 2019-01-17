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

#include "../includes/libft.h"

static size_t	ft_count_st(long long int num)
{
	size_t					count;
	unsigned long long int	n;

	count = 1;
	n = (unsigned long long int)(num < 0 && count++ ? num * -1 : num);
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(long long int num)
{
	char					*str;
	size_t					lenth;
	unsigned long long int	n;

	lenth = ft_count_st(num);
	if (!(str = (char *)malloc(sizeof(char) * lenth + 1)))
		return (NULL);
	if (num < 0 && (*str = '-'))
		n = (unsigned long long int)(num * -1);
	else
		n = (unsigned long long int)num;
	str[lenth--] = '\0';
	while (n >= 10)
	{
		str[lenth--] = n % 10 + '0';
		n /= 10;
	}
	str[lenth] = n + '0';
	return (str);
}
