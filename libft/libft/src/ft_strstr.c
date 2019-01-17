/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:51:17 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/29 18:34:31 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	n;
	size_t	i;
	char	*result;

	result = (char*)haystack;
	i = 0;
	if (needle[0] == '\0')
		return (result);
	while (haystack[i] != '\0')
	{
		n = 0;
		while (haystack[i + n] == needle[n])
		{
			++n;
			if (needle[n] == '\0')
				return (&result[i]);
		}
		i++;
	}
	return (0);
}
