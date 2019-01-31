/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:02:03 by oivanyts          #+#    #+#             */
/*   Updated: 2019/01/17 13:02:09 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_header.h"

static inline int	mesure_distance(int ax, int ay, int bx, int by)
{
	return ((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

static void			mark_field(struct s_coordinates new, int **map)
{
	struct s_coordinates	local;
	int						current;

	local.x = 0;
	while (local.x < g_map_size.x)
	{
		local.y = 0;
		while (local.y < g_map_size.y)
		{
			current = mesure_distance(local.x, local.y, new.x, new.y);
			if ((map[local.x][local.y] > 0 && (map[local.x][local.y] > current))
				|| map[local.x][local.y] == 0)
				map[local.x][local.y] = current;
			local.y++;
		}
		local.x++;
	}
}

static void			map_scan(int **field)
{
	char					*tmp;
	struct s_coordinates	scan;

	while (scan.x < g_map_size.x && get_next_line(VMFD, &tmp) && !(scan.y = 0))
	{
		while (scan.y < g_map_size.y)
		{
			if (field[scan.x][scan.y] != ENEMY && tmp[4 + scan.y] != '.' &&
			tmp[4 + scan.y] != g_dot && (field[scan.x][scan.y] = ENEMY) < 0)
				mark_field(scan, field);
			else if (tmp[4 + scan.y] == g_dot && (g_botlimit.x = scan.x) >= 0)
			{
				field[scan.x][scan.y] = FRIEND;
				if (scan.x < g_uplimit.x)
					g_uplimit.x = scan.x;
				if (scan.y < g_uplimit.y)
					g_uplimit.y = scan.y;
				if (g_botlimit.y < scan.y)
					g_botlimit.y = scan.y;
			}
			scan.y++;
		}
		scan.x++;
		free(tmp);
	}
}

static int			**first_line(char *line)
{
	char	*tmp;
	int		**field;

	if (line[10] == '1')
		g_dot = 'O';
	else if (line[10] == '2')
		g_dot = 'X';
	free(line);
	get_next_line(VMFD, &tmp);
	g_map_size.x = (int8_t)ft_atoi(&tmp[8]);
	g_map_size.y = (int8_t)ft_atoi(&tmp[8 + ft_num_size(g_map_size.x)]);
	g_uplimit = g_map_size;
	field = (int **)ft_matrixalloc(g_map_size.x, g_map_size.y, 4);
	free(tmp);
	get_next_line(VMFD, &tmp);
	free(tmp);
	map_scan(field);
	get_next_line(VMFD, &tmp);
	g_part_size.x = (int8_t)ft_atoi(&tmp[6]);
	g_part_size.y = (int8_t)ft_atoi(&tmp[6 + ft_num_size(g_part_size.x)]);
	g_newfigure = (int32_t **)ft_matrixalloc(100, 100, sizeof(int32_t));
	free(tmp);
	part_definition(tmp, field);
	return (field);
}

int					main(void)
{
	char	*line;
	int		**field;

	field = NULL;
	while (get_next_line(VMFD, &line))
	{
		if (ft_strstr(line, "$$$ exec p"))
			field = first_line(line);
		else if (ft_strstr(line, "Plateau "))
		{
			free(line);
			get_next_line(VMFD, &line);
			free(line);
			map_scan(field);
			get_next_line(VMFD, &line);
			free(line);
			g_part_size.x = (int8_t)ft_atoi(&line[6]);
			g_part_size.y = (int8_t)ft_atoi(&line[6 +
										ft_num_size(g_part_size.x)]);
			part_definition(line, field);
		}
	}
	free(line);
	free_fields(field);
	return (1);
}
