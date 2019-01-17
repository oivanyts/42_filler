/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:47:53 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/15 14:48:05 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

size_t	ft_strlen_u(wchar_t *str)
{
	int		i;
	size_t	counter;

	counter = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] <= 0x7F)
			counter++;
		else if (str[i] <= 0x7FF)
			counter += 2;
		else if (str[i] <= 0xFFFF)
			counter += 3;
		else
			counter += 4;
		i++;
	}
	return (counter);
}
