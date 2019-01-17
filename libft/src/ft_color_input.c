/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:00:04 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/14 17:00:53 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

const char	*g_colortab[9] = { "{black}", "{red}", "{green}", "{yellow}",
	"{blue}", "{magenta}", "{cyan}", "{white}", "{eoc}"};

void	ft_color_input(char *color)
{
	char	a[2];
	int		n;

	a[0] = '3';
	write(1, "\033[", 2);
	n = 0;
	while (!ft_strnstr(color, g_colortab[n], ft_strlen(g_colortab[n])))
		n++;
	if (n < 9 && (a[1] = n + '0'))
		write(1, &a, 2);
	else
		write(1, "0", 1);
	write(1, "m", 1);
}

char	*ft_check_color(const char *str)
{
	int		i;
	char	*ret;

	while (*str)
	{
		i = 0;
		while (*str == '{' && i <= 8)
		{
			if ((ret = ft_strnstr(str, g_colortab[i],
					ft_strlen(g_colortab[i]))))
				return (ret);
			i++;
		}
		str++;
	}
	return (NULL);
}
