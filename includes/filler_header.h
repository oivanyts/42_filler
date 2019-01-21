/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:11:18 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/17 13:11:21 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_HEADER_H
# define FILLER_HEADER_H

# define TRUE 1
# define FALSE 0
# define ENEMY -9
# define FRIEND -1

# include <stdbool.h>
# include "../libft/includes/libftprintf.h"

int		g_mapsize[2];
int		g_patr[2];
double 	**g_field;
char	g_dot;

int 	fd;
#endif