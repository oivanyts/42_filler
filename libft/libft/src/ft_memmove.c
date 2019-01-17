/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:14:34 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/02 16:57:33 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*des;
	unsigned const char	*sor;

	sor = (unsigned char *)src;
	des = (unsigned char *)dst;
	while (len--)
	{
		if (des <= sor)
			*des++ = *sor++;
		else
			des[len] = sor[len];
	}
	return (dst);
}
