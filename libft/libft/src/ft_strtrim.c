/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:55:56 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/01 13:44:32 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_countspace(const char *c, int direction)
{
	size_t	counter;

	counter = 0;
	while (*c && (*c == ' ' || *c == '\n' || *c == '\t'))
	{
		c += direction;
		counter++;
	}
	return (counter);
}

char			*ft_strtrim(char const *s)
{
	char	*fresh;
	size_t	trim_front;
	size_t	len;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	trim_front = ft_countspace(s, 1);
	if (len == trim_front)
		k = 0;
	else
		k = len - trim_front - ft_countspace(&s[len - 1], -1);
	if (!(fresh = (char *)malloc(k + 1)))
		return (NULL);
	while (k > i)
		fresh[i++] = s[trim_front++];
	fresh[k] = '\0';
	return (fresh);
}
