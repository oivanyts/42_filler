/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:44:25 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/31 16:22:37 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*des;
	unsigned const char	*sor;

	sor = (unsigned char *)src;
	des = (unsigned char *)dst;
	while (n--)
	{
		if (*sor == (unsigned char)c)
		{
			*des++ = *sor++;
			return (des);
		}
		*des++ = *sor++;
	}
	return (NULL);
}
