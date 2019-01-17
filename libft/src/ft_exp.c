/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:28:12 by oivanyts          #+#    #+#             */
/*   Updated: 2018/12/20 14:29:25 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	ft_exp(int num, int exp)
{
	if (exp == 0)
		return (1);
	else if (exp == 1)
		return (num);
	else if (exp < 0)
		return (1 / ft_exp(num, -exp));
	else
		return (num * ft_exp(num, exp - 1));
}
