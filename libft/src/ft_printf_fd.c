/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 09:42:51 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/18 09:43:10 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		ret;
	char	*tmp;
	char	*color;
	va_list	args;

	ret = 0;
	if ((tmp = ft_strchr(format, '%')))
	{
		va_start(args, format);
		while ((color = ft_check_color(format)) || tmp)
			if ((tmp = ft_strchr(format, '%')) && (tmp < color || !color) &&
				(ret += write(fd, format, tmp - format)) > -1)
			{
				format = tmp + 1;
				ret += ft_parcer_printf(&format, args, fd);
			}
			else if (color && (tmp > color || !tmp) &&
			(ret += write(fd, format, color - format) > -1))
			{
				format = ft_strchr(color, '}') + 1;
				ft_color_input(color);
			}
		va_end(args);
	}
	return (ret + (int)write(fd, format, ft_strlen(format)));
}
