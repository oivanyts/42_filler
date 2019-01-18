/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:40:37 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/30 15:40:45 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int		format_string(va_list arg, t_format fx, int fd)
{
	char	*tmp;
	size_t	add;
	size_t	counter;
	char	empty;

	empty = (char)(fx.flag[3] == '0' && fx.flag[0] != '-' ? '0' : ' ');
	if (!(tmp = va_arg(arg, char *)))
		tmp = "(null)";
	counter = ft_strlen(tmp);
	if (fx.precs >= 0 && ((size_t)fx.precs < counter))
		counter = (size_t)fx.precs;
	add = fx.whidth && fx.whidth > (int)counter ? (size_t)fx.whidth - counter
												: 0;
	if (fx.flag[0] == '-')
		write(fd, tmp, counter);
	while (add--)
		write(fd, &empty, 1);
	if (fx.flag[0] != '-')
		write(fd, tmp, counter);
	if (fx.whidth && fx.whidth > (int)counter)
		return (fx.whidth);
	else
		return ((int)counter);
}

int		format_string_u(va_list arg, t_format fx, int fd)
{
	wchar_t	*tmp;
	size_t	add;
	int		counter;
	wchar_t	empty;

	empty = (wchar_t)(fx.flag[3] == '0' && fx.flag[0] != '-' ? L'0' : L' ');
	if (!(tmp = va_arg(arg, int *)))
		tmp = L"(null)";
	if ((MB_CUR_MAX < ft_charlen(*tmp)))
		return (-1);
	if (fx.precs >= 0)
		tmp = ft_strndup_u(tmp, fx.precs);
	counter = (int)ft_strlen_u(tmp);
	add = fx.whidth && fx.whidth > counter ? (size_t)fx.whidth - counter : 0;
	counter = 0;
	counter += fx.flag[0] == '-' ? ft_putstr_u(tmp, fd) : 0;
	while (add--)
		counter += write(fd, &empty, 1);
	counter += fx.flag[0] != '-' ? ft_putstr_u(tmp, fd) : 0;
	if (fx.precs >= 0)
		free(tmp);
	return (counter);
}

int		formated_print(va_list arg, t_format fx, int fd)
{
	int		counter;
	char	*str;

	if (ft_strchr("diuoxXpfFDUObe", fx.type))
		str = form_numbers(arg, fx);
	else if (fx.type == 'S' || (fx.type == 's' && fx.mods == 'l'))
		return (format_string_u(arg, fx, fd));
	else if (fx.type == 's')
		return (format_string(arg, fx, fd));
	else
		return (format_char(arg, fx, fd));
	ft_putstr_fd(str, fd);
	counter = (int)ft_strlen(str);
	free(str);
	return (counter);
}

void	zero_struct(t_format *list)
{
	ft_memset(list->flag, '@', 5);
	list->mods = 0;
	list->precs = INT_MIN;
	list->whidth = 0;
}

int		ft_printf(const char *format, ...)
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
				(ret += write(1, format, tmp - format)) > -1)
			{
				format = tmp + 1;
				ret += ft_parcer_printf(&format, args, 1);
			}
			else if (color && (tmp > color || !tmp) &&
				(ret += write(1, format, color - format) > -1))
			{
				format = ft_strchr(color, '}') + 1;
				ft_color_input(color);
			}
		va_end(args);
	}
	return (ret + (int)write(1, format, ft_strlen(format)));
}
