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

//static float	mesure_distance(int ax, int ay, int bx, int by)
//{
//	return (sqrtf((ax - bx) * (ax - bx) +  (ay - by) * (ay - by)));
//}

int				min_of9(int8_t x, int8_t y)
{
	int	 	min;
	struct coordinates	tmp;

	min = INT_MAX;
	tmp.x = x - 1;
	tmp.x *= (tmp.x >= 0);
	while (tmp.x <= x + 1 && tmp.x < g_field_size.x)
	{
		tmp.y = y - 1;
		tmp.y *= (tmp.y >= 0);
		while (tmp.y <= y + 1 && tmp.y < g_field_size.y)
		{
			if (g_field[tmp.x][tmp.y] == -9)
			{
				g_field[x][y] = 1;
				return (1);
			}
			if (g_field[tmp.x][tmp.y] > 0 && min > g_field[tmp.x][tmp.y] && g_field[tmp.x][tmp.y] != -1)
				min = g_field[tmp.x][tmp.y];
			tmp.y++;
		}
		tmp.x++;
	}
	if (min + 1 > g_field[x][y])
		return (g_field[x][y] = min + 1);
	return (0);
}

int				check_field(int8_t x, int8_t y)
{
	int s;
	if (x == g_field_size.x)
		return (0);
	else if (y == g_field_size.y)
		return (check_field(x + 1, 0));
	else if (!(s = min_of9(x, y)))
	{
		ft_printf_fd(fd, "rec [%d:%d] = %d\n", x, y, s);
		return (check_field(x, y + 1));
	}
	else
		return (check_field(0, 0));

}

static void		mark_field(int8_t x, int8_t y)
{
	int8_t	i;
	int8_t	j;
	int8_t	round = 1;
//	int 	min;

	while (round <= g_field_size.x && round <= g_field_size.y)
	{
		i = x - round;
		i *= i > 0;
		while (i < g_field_size.x && i >= 0 && i <= x + round)
		{
			j = y - round;
			j *= j > 0;
			while (j < g_field_size.y && j >= 0 && j <= y + round)
			{
				if (g_field[i][j] != -9)
					min_of9(i, j);
				j++;
			}
			i++;
		}
//		ft_printf_fd(fd, "RND - %d ended\n", round);
//		print_matr(g_field, g_field_size.x, g_field_size.y);
		round++;
	}
}
//static void		mark_field(int8_t x, int8_t y, TFIELD **map)
//{
//	int8_t	i;
//	int8_t	j;
//	TFIELD	current;
//
//	i = 0;
//	while (i < g_field_size.x)
//	{
//		j = 0;
//		while (j < g_field_size.y)
//		{
//			current = mesure_distance(i, j, x, y);
//			if ((map[i][j] > 0 && (map[i][j] > current)) || map[i][j] == 0)
//				map[i][j] = current;
//			j++;
//		}
//		i++;
//	}
//}


//static void		mark_farest(int8_t x, int8_t y)
//{
//	int8_t	i;
//	int8_t	j;
//	TFIELD	current;
//
//	i = 0;
//	while (i < g_field_size.x)
//	{
//		j = 0;
//		while (j < g_field_size.y)
//		{
//			if (g_field[i][j] == -9 && (current = mesure_distance(i, j, x, y)) > g_how_far)
//			{
//				g_how_far = current;
//				g_farest_enemy.x = i;
//				g_farest_enemy.y = j;
//				mark_field(i, j, g_field);
//				ft_printf_fd(fd, "Now farest spot is [%d:%d]\n", i, j);
//			}
//			j++;
//		}
//		i++;
//	}
//}

static TFIELD	valid_sum(int8_t x, int8_t y)
{
	int8_t	count_friends;
	int8_t	i;
	int8_t	j;
	TFIELD	sum;

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
				if (g_field[x + i][y + j] > 1)
					sum += g_field[x + i][y + j] * g_newfigure[i][j];
			j++;
		}
		i++;
	}
//	ft_printf_fd(fd, "for [%2d:%2d] - sum = %.2f\n", x, y, sum);
	return (TFIELD)(count_friends == 1 ? (sum) : (-1));
}

void			search_point(void)
{
	int8_t	i;
	int8_t	j;
	int32_t	tmp;

	g_best_result.x = 0;
	g_best_result.y = 0;
	g_best_sum = INT_MAX;
	i = (int8_t)(g_friend_start.x - g_new_part.x + 1);
	i *= (i > 0);
	ft_printf_fd(fd, "\nStart [%d:%d] FINISH [%d:%d] \n", g_friend_start.x, g_friend_start.y, g_friend_finish.x, g_friend_finish.y);
	while (i <= g_friend_finish.x && (i + g_new_part.x) <= g_field_size.x)
	{
		j = (int8_t)(g_friend_start.y - g_new_part.y + 1);
		j *= (j > 0);
		while (j <= g_friend_finish.y && (j + g_new_part.y) <= g_field_size.y)
		{
			if ((tmp = valid_sum(i, j)) >= 0 && tmp < g_best_sum)
			{
//				ft_printf_fd(fd, "\nSum at [%d:%d] - %d\n", i, j, tmp);
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

	while (x < g_field_size.x && get_next_line(fd1, &tmp))
	{
		ft_printf_fd(fd, "%s\n", tmp);
		y = 0;
		while (y < g_field_size.y)
		{
			if (tmp[4 + y] != '.' && tmp[4 + y] != g_dot && g_field[x][y] != ENEMY)
			{
				g_field[x][y] = ENEMY;
				if (g_first_enemy.x == 0 && g_first_enemy.y == 0)
					mark_field(x, y);
			}
			else if (tmp[4 + y] == g_dot)
			{
				g_field[x][y] = FRIEND;
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
		g_field = (TFIELD **)ft_matrixalloc(g_field_size.x, g_field_size.y, sizeof(TFIELD));
		free(tmp);
		get_next_line(fd1, &tmp);
		free(tmp);
		map_scan(0, 0);
		check_field(0, 0);
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
			check_field(0, 0);
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
