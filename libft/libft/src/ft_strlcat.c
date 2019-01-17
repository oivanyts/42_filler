/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:42:30 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/08 17:15:39 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len_dst;
	size_t t;
	size_t n;

	n = 0;
	len_dst = ft_strlen(dst);
	t = len_dst;
	if (size < len_dst)
		return (ft_strlen(src) + size);
	while (src[n] && t < size)
		dst[t++] = src[n++];
	if (!src[n])
		dst[t] = '\0';
	if (n && n == size - len_dst)
		dst[t - 1] = '\0';
	return (len_dst + ft_strlen(src));
}
