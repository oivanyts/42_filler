/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 10:08:11 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/11 10:08:15 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_charlen(wchar_t c)
{
	size_t	counter;

	counter = 0;
	if (c <= 0x7F)
		counter++;
	else if (c <= 0x7FF)
		counter += 2;
	else if (c <= 0xFFFF)
		counter += 3;
	else
		counter += 4;
	return (counter);
}
