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

# define ENEMY -9
# define FRIEND -1

# include "../libft/includes/libftprintf.h"
# include <stdio.h>
# include <errno.h>
# include <math.h>
# define TFIELD float
struct	coordinates
{
	int8_t x;
	int8_t y;
};

struct	coordinates	g_field_size;
struct	coordinates	g_new_part;
struct	coordinates	g_friend_start;
struct	coordinates	g_friend_finish;
struct	coordinates	g_best_result;
struct	coordinates	g_first_enemy;

TFIELD				**g_field;
TFIELD				**g_farest;
TFIELD				g_how_far;
int32_t				**g_newfigure;
int32_t 			g_best_sum;

void	print_matr(TFIELD **matr, int8_t matr_x, int8_t matr_y);

char				g_dot;


int 				err_log;
int 				fd;
int 				fd1;
#endif
