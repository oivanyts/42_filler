/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:53:12 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/29 19:05:44 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*result;

	result = (char *)s;
	i = ft_strlen(result) + 1;
	while (i-- > 0)
		if (result[i] == (unsigned char)c)
			return (&result[i]);
	return (NULL);
}
