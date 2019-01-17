/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:24:38 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/31 15:55:28 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	fresh = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!fresh)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		fresh[i] = s1[i];
		i++;
	}
	while (n < ft_strlen(s2))
	{
		fresh[i + n] = s2[n];
		n++;
	}
	fresh[i + n] = '\0';
	return (fresh);
}
