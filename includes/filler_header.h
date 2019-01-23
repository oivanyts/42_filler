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

struct coordinates
{
	int8_t x;
	int8_t y;
};



struct coordinates	g_mapsize;
struct coordinates	g_new_part;
struct coordinates	g_friend_start;
struct coordinates	g_friend_finish;
struct coordinates	g_best_result;

float **g_field;
int32_t	**g_newfigure;
float g_best_sum;

char	g_dot;

int 	fd;
int 	fd1;
#endif
