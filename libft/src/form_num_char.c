/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_num_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 10:01:19 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/11 10:01:29 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static long long int			mod_int(va_list arg, t_format fx)
{
	if (fx.mods == 'm' || fx.mods == 'j' || fx.type == 'D')
		return (va_arg(arg, long long int));
	else if (fx.mods == 'l' || fx.mods == 'z')
		return (va_arg(arg, long int));
	else if (fx.mods == 'c')
		return ((char)va_arg(arg, int));
	else if (fx.mods == 's')
		return ((short int)va_arg(arg, int));
	return (va_arg(arg, int));
}

static unsigned long long int	mod_u_int(va_list arg, t_format fx)
{
	if (fx.mods == 'm' || fx.mods == 'j' || fx.type == 'U' || fx.type == 'O')
		return (va_arg(arg, unsigned long long int));
	else if (fx.mods == 'l' || fx.mods == 'z' || fx.type == 'p')
		return (va_arg(arg, unsigned long int));
	else if (fx.mods == 'c')
		return ((unsigned char)va_arg(arg, int));
	else if (fx.mods == 's')
		return ((unsigned short int)va_arg(arg, int));
	return (va_arg(arg, unsigned int));
}

static int						fill_bit_union(va_list arg, t_format fx)
{
	if (fx.mods == 'L')
		u_ni.l_d = va_arg(arg, long double);
	else if (fx.mods == 'l')
		u_ni.d = va_arg(arg, double);
	else
		u_ni.l_i = mod_u_int(arg, fx);
	return (1);
}

char							*form_numbers(va_list arg, t_format fx)
{
	char	*str;
	int		i;

	i = 0;
	if (fx.type == 'd' || fx.type == 'i' || fx.type == 'D')
		str = ft_itoa_prntf(mod_int(arg, fx), fx);
	else if (fx.type == 'u' || fx.type == 'U')
		str = ft_strnum_base(mod_u_int(arg, fx), 10, fx);
	else if (fx.type == 'X' || fx.type == 'x' || fx.type == 'p')
	{
		str = ft_strnum_base(mod_u_int(arg, fx), 16, fx);
		if (fx.type == 'x' || fx.type == 'p')
			while (str[i++])
				str[i - 1] = (char)ft_tolower(str[i - 1]);
	}
	else if (fx.type == 'o' || fx.type == 'O')
		str = ft_strnum_base(mod_u_int(arg, fx), 8, fx);
	else if (fx.type == 'b' && fill_bit_union(arg, fx))
		str = ft_printbits(u_ni.str, fx);
	else
		str = ft_itoa_double(fx.mods == 'L' ?
				va_arg(arg, long double) : va_arg(arg, double), fx);
	return (str);
}

int								format_char(va_list arg, t_format fx, int fd)
{
	int				print;
	char			empty;
	int				i;
	int				ret;

	i = 1;
	ret = 1;
	empty = fx.flag[3] == '0' && fx.flag[0] != '-' ? '0' : ' ';
	print = fx.type == 'c' || fx.type == 'C' ? va_arg(arg, int) : fx.type;
	while (fx.flag[0] != '-' && (i++ < fx.whidth))
		write(1, &empty, 1);
	if (fx.type == 'C' || (fx.type == 'c' && fx.mods == 'l'))
		ret = ft_putchar_u(print, fd);
	else
		write(fd, &print, 1);
	if ((MB_CUR_MAX < ft_charlen(print)))
		ret = -1;
	while (fx.flag[0] == '-' && (i++ < fx.whidth))
		write(fd, &empty, 1);
	return (fx.whidth ? fx.whidth : ret);
}
