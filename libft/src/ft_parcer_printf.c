/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:33:46 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/14 17:33:51 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int	f_precs(const char **w, va_list arg)
{
	int ret;

	*w += 1;
	if (**w == '*' && (*w += 1))
		return (va_arg(arg, int));
	ret = ft_atoi(*w);
	while (ft_isdigit(**w))
		*w += 1;
	return (ret);
}

static int	f_whidth(const char **w, va_list arg, t_format *fx)
{
	int	ret;

	if (**w == '*' && (*w += 1))
	{
		ret = va_arg(arg, int);
		if (ret < 0 && (fx->flag[0] = '-'))
			return (-ret);
		else
			return (ret);
	}
	ret = ft_atoi(*w);
	while (ft_isdigit(**w))
		*w += 1;
	return (ret);
}

static char	f_mods(const char **m)
{
	char ret;

	if (**m == 'h' && (*m += 1))
		return (char)(**m == 'h' && (*m += 1) ? 'c' : 's');
	else if (**m == 'l' && (*m += 1))
		return (char)(**m == 'l' && (*m += 1) ? 'm' : 'l');
	else if (**m == 'L' || **m == 'z' || **m == 'j')
	{
		ret = **m;
		*m += 1;
		return (ret);
	}
	return (0);
}

static char	f_flags(const char **flag, t_format *list)
{
	if (**flag == '-' && (*flag += 1))
		return (list->flag[0] = '-');
	if (**flag == '+' && (*flag += 1))
		return (list->flag[1] = '+');
	if (**flag == ' ' && (*flag += 1))
		return (list->flag[2] = ' ');
	if (**flag == '0' && (*flag += 1))
		return (list->flag[3] = '0');
	if (**flag == '#' && (*flag += 1))
		return (list->flag[4] = '#');
	return (0);
}

int			ft_parcer_printf(const char **str, va_list arg, int fd)
{
	t_format	fx;

	zero_struct(&fx);
	while (**str)
	{
		if (f_flags(str, &fx))
			;
		else if (ft_isdigit(**str) || **str == '*')
			fx.whidth = f_whidth(str, arg, &fx);
		else if (**str == '.')
			fx.precs = f_precs(str, arg);
		else if (ft_strchr("hlLzj", **str))
			if (fx.mods && ft_strchr("zj", fx.mods))
				*str += 1;
			else
				fx.mods = f_mods(str);
		else
		{
			fx.type = **str;
			*str += 1;
			return (formated_print(arg, fx, fd));
		}
	}
	return (0);
}
