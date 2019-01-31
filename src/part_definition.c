/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_definition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:01:13 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/30 12:01:17 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_header.h"

static int	valid_sum(struct s_coordinates part, int **field)
{
	int8_t				count_friends;
	struct s_coordinates	tmp;
	int					sum;

	sum = 0;
	count_friends = 0;
	tmp.x = 0;
	while (tmp.x < g_part_size.x)
	{
		tmp.y = 0;
		while (tmp.y < g_part_size.y)
		{
			if (g_newfigure[tmp.x][tmp.y] && (((field[part.x + tmp.x][part.y +
			tmp.y] == FRIEND) && ++count_friends > 1) ||
			field[part.x + tmp.x][part.y + tmp.y] == ENEMY))
				return (-1);
			if (field[part.x + tmp.x][part.y + tmp.y] > -1)
				sum += field[part.x + tmp.x][part.y + tmp.y] *
						g_newfigure[tmp.x][tmp.y];
			tmp.y++;
		}
		tmp.x++;
	}
	return (count_friends == 1 ? (sum) : (-1));
}

static void	search_point(int **g_field)
{
	struct s_coordinates	tmp;
	struct s_coordinates	result;
	int32_t				sum;

	result.x = 0;
	result.y = 0;
	g_best_sum = INT_MAX;
	tmp.x = (int8_t)(g_uplimit.x - g_part_size.x + 1);
	tmp.x *= (tmp.x > 0);
	while (tmp.x <= g_botlimit.x && (tmp.x + g_part_size.x) <= g_map_size.x)
	{
		tmp.y = (int8_t)(g_uplimit.y - g_part_size.y + 1);
		tmp.y *= (tmp.y > 0);
		while (tmp.y <= g_botlimit.y && (tmp.y + g_part_size.y) <= g_map_size.y)
		{
			if ((sum = valid_sum(tmp, g_field)) >= 0 && sum < g_best_sum)
			{
				g_best_sum = sum;
				result = tmp;
			}
			tmp.y++;
		}
		tmp.x++;
	}
	ft_printf("%d %d\n", result.x, result.y);
}

void		part_definition(char *tmp, int **g_field)
{
	struct s_coordinates	local;
	struct s_coordinates	last;

	local.x = 0;
	last.x = 0;
	while (local.x < g_part_size.x && get_next_line(VMFD, &tmp))
	{
		local.y = 0;
		while (local.y < g_part_size.y)
		{
			if (tmp[local.y] == '*' && (last.x = local.x) >= 0)
			{
				if ((g_newfigure[local.x][local.y] = 1) && local.y > last.y)
					last.y = local.y;
			}
			else
				g_newfigure[local.x][local.y] = 0;
			local.y++;
		}
		local.x++;
		free(tmp);
	}
	g_part_size.x = (int8_t)(last.x + 1);
	g_part_size.y = (int8_t)(last.y + 1);
	search_point(g_field);
}

void		free_fields(int **field)
{
	int i;

	i = 0;
	while (i < g_map_size.x)
		free(field[i++]);
	free(field);
	i = 0;
	while (i < 100)
		free(g_newfigure[i++]);
	free(g_newfigure);
}
