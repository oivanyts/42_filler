/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:37:19 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/29 18:06:47 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	i;
	char	*result;

	result = (char*)haystack;
	i = 0;
	if (needle[0] == '\0')
		return (result);
	while (haystack[i] != '\0' && i < len)
	{
		n = 0;
		while (haystack[i + n] == needle[n] && ((i + n) < len))
		{
			++n;
			if (needle[n] == '\0')
				return (&result[i]);
		}
		i++;
	}
	return (0);
}
