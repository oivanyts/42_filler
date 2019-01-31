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
# define VMFD 0

# include "../libft/includes/libftprintf.h"
# include <stdio.h>
# include <errno.h>

struct	s_coordinates
{
	int8_t x;
	int8_t y;
};

struct s_coordinates	g_map_size;
struct s_coordinates	g_part_size;
struct s_coordinates	g_uplimit;
struct s_coordinates	g_botlimit;

int32_t					**g_newfigure;
int32_t					g_best_sum;
char					g_dot;

void					part_definition(char *tmp, int **g_field);
void					free_fields(int **field);

#endif
