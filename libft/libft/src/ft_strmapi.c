/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:24:58 by oivanyts          #+#    #+#             */
/*   Updated: 2018/10/31 13:50:51 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	unsigned int	i;
	unsigned int	n;

	n = 0;
	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(fresh = malloc((ft_strlen(s)) + 1)))
		return (NULL);
	while (s[n])
	{
		fresh[i++] = f(n, s[n]);
		n++;
	}
	fresh[i] = '\0';
	return (fresh);
}
