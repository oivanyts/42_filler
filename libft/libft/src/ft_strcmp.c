/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:50:24 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/06 14:53:11 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int n;

	n = 0;
	while (s1[n] && s2[n])
	{
		if (s1[n] == s2[n])
			n++;
		else
			return ((unsigned char)s1[n] - (unsigned char)s2[n]);
	}
	return ((unsigned char)s1[n] - (unsigned char)s2[n]);
}
