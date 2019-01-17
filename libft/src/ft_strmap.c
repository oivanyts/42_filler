/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:09:55 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:00 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	fresh = malloc((ft_strlen(s)) + 1);
	if (!fresh)
		return (NULL);
	while (*s)
		fresh[i++] = f(*s++);
	fresh[i] = '\0';
	return (fresh);
}
