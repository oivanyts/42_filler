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

static int32_t	mesure_distance(int ax, int ay, int bx, int by)
{
	return ((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}



//int32_t min_sum(int8_t x, int8_t y, int32_t **map)
//{
//	int32_t sum;
//	int32_t min_s;
//	struct coordinates	tmp;
//	struct coordinates	min;
//
//	min_s = INT_MAX;
//	tmp.x = x - 1;
//	tmp.x *= (tmp.x > 0);
////	while (tmp.x <= x + 1 && tmp.x < g_field_size.x)
////	{
////		tmp.y = y - 1;
////		tmp.y *= (tmp.y > 0);
////		while (tmp.y <= y + 1 && tmp.y < g_field_size.y )
////		{
////			if (map[tmp.x][tmp.y] > 0)
////			{
////				if (map[tmp.x][tmp.y] < min_s)
////				{
////					min_s = map[tmp.x][tmp.y];
////					min = tmp;
////				}
////			}
////			tmp.y++;
////		}
////		tmp.x++;
////	}
////	if (min.x == x)
////		return (map[min.x - 1][min.y] >	map[min.x + 1][min.y] ? map[min.x + 1][min.y] : map[min.x - 1][min.y]);
////	if (min.y == y)
////		return (map[min.x][min.y - 1] >	map[min.x][min.y + 1] ? map[min.x][min.y + 1] : map[min.x][min.y - 1]);
////	if (min.x > x)
////
//	return (sum);
//}
static void		close_distance(int8_t x, int8_t y, int32_t **map)
{
	int8_t i;
	int8_t j;
	int8_t round;

	round = 1;
	while (1)
	{
		i = x - round;
		i *= (i > 0);
		while (i <= x + round && i < g_field_size.x)
		{
			j = y - round;
			y *= (j > 0);
			while (j <= y + round && j < g_field_size.y )
			{
				if (map[i][j] != -9 && round == 1)
					map[i][j] = (i != x) + (j != y);
				else if (map[i][j] != -9)
					map[i][j] = round;
				j++;
			}
			i++;
		}
		round++;
		if (i == g_field_size.x && j == g_field_size.y)
			break ;
	}

}

static void		mark_field(int8_t x, int8_t y, int32_t **map)
{
	int8_t	i;
	int8_t	j;
	int32_t	current;

	close_distance(x, y, map);
//	ft_printf_fd(fd, "\n\n matr 1\n");
//	print_matr(map, g_field_size.x, g_field_size.y);
//	ft_printf_fd(fd, "\n\n matr 1\n");

	i = 0;
	while (i < g_field_size.x)
	{
		j = 0;
		while (j < g_field_size.y)
		{
			current = mesure_distance(i, j, x, y) ;
			if ((map[i][j] > 0 && (map[i][j] > current)) || map[i][j] == 0)
				map[i][j] = current;
			j++;
		}
		i++;
	}
}

static int16_t	valid_sum(int8_t x, int8_t y)
{
	int8_t	count_friends;
	int8_t	i;
	int8_t	j;
	int32_t	sum;

	sum = 0;
	count_friends = 0;
	i = 0;
	while (i < g_new_part.x)
	{
		j = 0;
		while (j < g_new_part.y)
		{
			if (g_newfigure[i][j] && (((g_field[x + i][y + j] == -1) &&
			++count_friends > 1) || g_field[x + i][y + j] == -9))
				return (-1);
			else if (g_field[x + i][y + j] > -1)
				sum += g_field[x + i][y + j] * g_newfigure[i][j];
			j++;
		}
		i++;
	}
	return (int16_t)(count_friends == 1 ? (sum) : (0));
}

void			search_point(void)
{
	int8_t	i;
	int8_t	j;
	int16_t	tmp;

	g_best_result.x = 0;
	g_best_result.y = 0;
	g_best_sum = INT_MAX;
	i = (int8_t)(g_friend_start.x - g_new_part.x + 1);
	i *= (i > 0);
	ft_printf_fd(fd, "\nMAX PSBL X:Y [%d:%d] \n", g_field_size.x, g_field_size.y);
	while (i <= g_friend_finish.x && (i + g_new_part.x) <= g_field_size.x)
	{
		j = (int8_t)(g_friend_start.y - g_new_part.y + 1);
		j *= (j > 0);
		while (j <= g_friend_finish.y && (j + g_new_part.y) <= g_field_size.y)
		{
			if ((tmp = valid_sum(i, j)) > 0 && tmp <= g_best_sum)
			{
				g_best_sum = tmp;
				g_best_result.x = i;
				g_best_result.y = j;
			}
			j++;
		}
		i++;
	}
	print_matr(g_field, g_field_size.x , g_field_size.y);
	ft_printf_fd(fd, "\n[%d:%d] result\n\n", g_best_result.x, g_best_result.y);
}

void			part_definition(void)
{
	int8_t x;
	int8_t y;
	char	*tmp;
	int8_t last_x;
	int8_t last_y;

	x  = 0;
	last_y = 0;
	while (x < g_new_part.x && get_next_line(fd1, &tmp))
	{
		ft_printf_fd(fd, "%s\n", tmp);
		y = 0;
		while (y < g_new_part.y)
		{
			if (tmp[y] == '*' && (last_x = x) >= 0)
			{
				if ((g_newfigure[x][y] = 1) && y > last_y)
					last_y = y;
			}
			else
				g_newfigure[x][y] = 0;
			y++;
		}
		x++;
		free(tmp);
	}
	g_new_part.x = (int8_t)(last_x + 1);
	g_new_part.y = (int8_t)(last_y + 1);
	ft_printf_fd(fd, "\n [%d:%d] newpart-x:y\n", g_new_part.x , g_new_part.y);
	search_point();
}

void			map_scan(int8_t x, int8_t y)
{
	char    *tmp;
	int8_t count;

	count = 0;
	while (x < g_field_size.x && get_next_line(fd1, &tmp))
	{
		ft_printf_fd(fd, "%s\n", tmp);
		y = 0;
		while (y < g_field_size.y)
		{
			if (tmp[4 + y] != '.' && tmp[4 + y] != g_dot && g_field[x][y] != ENEMY)
			{
				g_field[x][y] = ENEMY;
				mark_field(x, y, g_field);
			}
			else if (tmp[4 + y] == g_dot)
			{
				g_field[x][y] = FRIEND;
				if (!count++ && ((g_friend_start.x = x) >= 0))
					g_friend_start.y = y;
				if (y < g_friend_start.y)
					g_friend_start.y = y;
				g_friend_finish.x = x;
				if (g_friend_finish.y < y)
					g_friend_finish.y = y;
			}
			y++;
		}
		x++;
		free(tmp);
	}
	ft_printf_fd(fd, "\n");
}

void			first_line(char *line)
{
	char 	*tmp;

	if (line[10] == '1')
		g_dot = 'O';
	else if (line[10] == '2')
		g_dot = 'X';
	get_next_line(fd1, &tmp);
	if (ft_strstr(tmp, "Plateau "))
	{
		g_field_size.x = (int8_t)ft_atoi(&tmp[8]);
		g_field_size.y = (int8_t)ft_atoi(&tmp[8 + ft_num_size(g_field_size.x)]);
		g_field = (int32_t **)ft_matrixalloc(g_field_size.x, g_field_size.y, sizeof(int32_t));
		free(tmp);
		get_next_line(fd1, &tmp);
		free(tmp);
		map_scan(0, 0);
		get_next_line(fd1, &tmp);
		g_new_part.x = (int8_t)ft_atoi(&tmp[6]);
		g_new_part.y = (int8_t)ft_atoi(&tmp[6 + ft_num_size(g_new_part.x)]);
		g_newfigure = (int32_t **)ft_matrixalloc(100, 100, sizeof(int32_t));
		part_definition();
		free(tmp);
	}
}

static void		fillit_parser(void)
{
	char *line;

	while (get_next_line(fd1, &line))
	{
		if (ft_strstr(line, "$$$ exec p"))
		{
			first_line(line);
			free(line);
		}
		else if (ft_strstr(line, "Plateau "))
		{
			get_next_line(fd1, &line);
			free(line);
			map_scan(0, 0);
			get_next_line(fd1, &line);
			g_new_part.x = (int8_t)ft_atoi(&line[6]);
			g_new_part.y = (int8_t)ft_atoi(&line[6 + ft_num_size(g_new_part.x)]);
			free(line);
			part_definition();
		}
		ft_printf("%d %d\n", g_best_result.x, g_best_result.y);
	}
}

int				main()
{
	if ((err_log = open("ttt.txt", O_RDWR)) == -1)
		return (22);
	if ((fd = open("test.txt", O_RDWR)) <= 0)
		exit(ft_printf_fd(err_log, "FAIL TO OPEN FILE err = %d", errno));
	fd1          = 0;
	fillit_parser();
	return (0);
}
