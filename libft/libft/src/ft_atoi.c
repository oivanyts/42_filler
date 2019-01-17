/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:13:03 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/06 15:20:33 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	x;
	int					znak;

	znak = 1;
	x = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while (ft_isdigit(*str))
		x = x * 10 + (*str++ - '0');
	if (x > LLONG_MAX && znak == 1)
		return (-1);
	if (x > LLONG_MAX && znak == -1)
		return (0);
	return (x * znak);
}
