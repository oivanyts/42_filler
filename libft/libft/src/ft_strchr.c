/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:17:20 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/29 18:52:21 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*result;

	result = (char *)s;
	i = 0;
	while (result[i])
		if (result[i++] == (unsigned char)c)
			return (&result[i - 1]);
	if (result[i] == (unsigned char)c)
		return (&result[i]);
	return (NULL);
}
