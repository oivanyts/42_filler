/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:53:44 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/26 15:54:24 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	ptr2 = (char *)src;
	ptr1 = (char *)dst;
	if (!n || ptr1 == ptr2)
		return (dst);
	while (n--)
		*ptr1++ = *ptr2++;
	return (dst);
}
