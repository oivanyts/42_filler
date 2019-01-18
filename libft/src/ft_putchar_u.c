/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:13:31 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/15 13:13:35 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_putchar_u(int c, int fd)
{
	char	ustr[4];
	int		size;

	if ((size = ft_charlen(c)) > MB_CUR_MAX)
		return (-1);
	if (size <= 1)
		return ((int)write(fd, &c, 1));
	else if ((ustr[3] = (char)((c & 0x3F) | 0x80)) && size <= 2)
	{
		ustr[2] = (char)(c >> 6 | 0xC0);
		return ((int)write(fd, &ustr[2], 2));
	}
	else if ((ustr[2] = (char)((c & 0xFC0) >> 6 | 0x80)) && size <= 3)
	{
		ustr[1] = (char)(c >> 12 | 0xE0);
		return ((int)write(fd, &ustr[1], 3));
	}
	else
	{
		ustr[0] = (char)(c >> 18 | 0xE0);
		ustr[1] = (char)((c & 0xF000) >> 12 | 0xE0);
		return ((int)write(fd, &ustr, 4));
	}
}
