/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:31:37 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/14 17:31:42 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

wchar_t	*ft_strndup_u(wchar_t *src, size_t n)
{
	size_t		i;
	wchar_t		*str;
	size_t		counter;

	counter = 0;
	if (!(str = malloc((sizeof(wchar_t) + 1) * n)))
		return (NULL);
	i = 0;
	while ((counter + ft_charlen(src[i])) <= n && src[i])
	{
		str[i] = src[i];
		counter += ft_charlen(src[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
