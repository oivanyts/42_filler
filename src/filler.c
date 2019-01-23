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
#include <math.h>

/*
 * prints matrix to
 */

//static void	print_matr(int fd)
//{
//	int i = 0;
//	int	j;
//	ft_printf_fd(fd, "\t   0\t1\t 2\t  3\t   4\t5\t 6\t  7\t   8\t 9\t 0\t  1\t  2\t    3\t 4\t 5\t   6\n ");
//	while (i < g_mapsize.x)
//	{
//		j = 0;
//		ft_printf_fd(fd, "%d\t{", i);
//		while (j < g_mapsize.y)
//		{
//			ft_printf_fd(fd, "%7.2f", g_field[i][j]);
//			j++;
//		}
//		i++;
//		ft_printf_fd(fd, "}\n");
//	}
//	ft_printf_fd(fd, "MATRIX PRINTED\n");
//}

static void	print_matr(int fd, float **matr, int8_t matr_x, int8_t matr_y)
{
	int i = 0;
	int	j;

	ft_printf_fd(fd, "\n\tMATRIX [%d]:[%d]\n", matr_x, matr_y);
	while (i < matr_x)
	{
		j = 0;
		ft_printf_fd(fd, "%d\t{ ", i);
		while (j < matr_y)
		{
			ft_printf_fd(fd, "%5d", (int)matr[i][j]);
			j++;
		}
		i++;
		ft_printf_fd(fd, "}\n");
	}
	ft_printf_fd(fd, "\tMATRIX PRINTED\n\n");
}

/*
 * add this to libary
 */

long long	ft_abs(long long num)
{
	return num >= 0 ? num : -num;
}


static float			mesure_distance(int ax, int ay, int bx, int by)
{
	return ((sqrtf((float)((ax - bx) * (ax - bx) + (ay - by) * (ay - by)))));
}

void		mark_field(int x, int y)
{
	int8_t	i;
	int8_t	j;
	float current;

	i = 0;
	while (i < g_mapsize.x)
	{
		j = 0;
		while (j < g_mapsize.y)
		{
			current = mesure_distance(i, j, x, y);
			if ((g_field[i][j] > 0 && (g_field[i][j] > current)) || g_field[i][j] == 0)
				g_field[i][j] = current;
			j++;
		}
		i++;
	}
//	print_matr(g_field, fd);
}

int16_t valid_sum(int8_t x, int8_t y)
{
	int8_t count_friends;
	int8_t i;
	int8_t j;
	int16_t sum;

	sum = 0;
	count_friends = 0;
	i = 0;
	while (i < g_new_part.x)
	{
		j = 0;
		while (j < g_new_part.y)
		{
			if (g_newfigure[i][j] && (((g_field[x + i][y + j] == -1) && ++count_friends > 1) || g_field[x + i][y + j] == -9))
				return (-1);
			else if (g_field[x + i][y + j] > -1)
				sum += g_field[x + i][y + j] * g_newfigure[i][j];
			j++;
		}
		i++;
	}
	ft_printf_fd(fd, " at [ %d:%d ] sum %d\n", x, y, sum*count_friends);
	return count_friends == 1 ? (sum) : (0);
}

void	search_point()
{
	int8_t i;
	int8_t j;
	int16_t tmp;

	g_best_sum = INT_MAX;
	if ((i = g_friend_start.x - g_new_part.x + 1) > 0)
		;
	else
		i = 0;
//	ft_printf_fd(fd, "++++ %d +++++\n ", __LINE__);
	while (i <= g_friend_finish.x && (i + g_new_part.x) <= g_mapsize.x)
	{
//		ft_printf_fd(fd, "++++ %d good on %d\n ", __LINE__, i);
		j = (g_friend_start.y - g_new_part.y + 1) > 0 ? g_friend_start.y - g_new_part.y + 1 : 0;
		while(j <= g_friend_finish.y && (j + g_new_part.y) <= g_mapsize.y)
		{
			if ((tmp = valid_sum(i, j)) > 0 && tmp < g_best_sum)
			{
				g_best_sum = tmp;
				g_best_result.x = i;
				g_best_result.y = j;
			}
			j++;
		}
		i++;
	}
//	ft_printf_fd(fd, "++++ %d +++++\n ", __LINE__);
	ft_printf_fd(fd, "\t>> spot {%d:%d}\n", g_best_result.x, g_best_result.y);
}

void	part_definition()
{
	int8_t	x;
	int8_t	y;
	char 	*tmp;

	x = 0;
	ft_printf_fd(fd, "++++ %d +++++\n", __LINE__);
	while (x < g_new_part.x)
	{
		if (!get_next_line(fd1, &tmp))
			exit(ft_printf_fd(fd, "dnlfail %d  on %d +++++\n ", __LINE__, x));
		y = 0;
		ft_printf_fd(fd, "{%s} ", tmp);
		while (y < g_new_part.y)
		{
			g_newfigure[x][y] = (int8_t)(tmp[y] == '*');
			y++;
		}
		ft_printf_fd(fd, "%d - done\n", x);
		x++;
//		free(tmp);
	}
	ft_printf_fd(fd, "++++ %d +++++\n ", __LINE__);
	print_matr(fd, (float **)g_newfigure, g_new_part.x, g_new_part.y);
	search_point();
}

void map_scan(int fd)
{
	int8_t	x = 0;
	char 	*tmp;
	int8_t	y;
	int16_t	count;

	count = 0;
	get_next_line(fd1, &tmp);
	free(tmp);
	ft_printf_fd(fd, "%-35s\n", tmp);
	while (x < g_mapsize.x && get_next_line(fd1, &tmp))
	{
		y = 0;
		ft_printf_fd(fd, "%-35s\n", tmp);
		while (y < g_mapsize.y)
		{
			if (tmp[4 + y] == 'O' || tmp[4 + y] == 'o')
			{
				g_field[x][y] = ENEMY;
				mark_field(x, y);
			}
			else if (tmp[4 +  y] == 'X' || tmp[4 + y] == 'x')
			{
				g_field[x][y] = FRIEND;
				if (!count++ && (g_friend_start.x = x) >= 0)
					g_friend_start.y = y;
				g_friend_finish.x = x;
				g_friend_finish.y = y;
			}
			y++;
		}
		x++;
		free(tmp);
	}
	print_matr(fd, g_field, g_mapsize.x, g_mapsize.y);
}

void		first_line(char *line, int fd)
{
	char	*tmp;
	if (line[10] == '1')
		g_dot = (char) 'o';
	else if (line[10] == '2')
		g_dot = (char) 'x';
	get_next_line(fd1, &tmp);
	if (ft_strstr(tmp, "Plateau "))
	{
		g_mapsize.x = (int8_t) ft_atoi(&tmp[8]);
		g_mapsize.y = (int8_t) ft_atoi(&tmp[8 + ft_num_size(g_mapsize.x)]);
		g_field = (float **)ft_matrixalloc(g_mapsize.x, g_mapsize.y, sizeof(float));
//		ft_printf_fd(fd, "MATRIX START\n gxm - %d, gym - %d\n", g_mapsize[0], g_mapsize[1]);
//		print_matr(fd);
		map_scan(fd);
		free(tmp);
		get_next_line(fd1, &tmp);
		g_new_part.x = (int8_t)ft_atoi(&tmp[6]);
		g_new_part.y = (int8_t)ft_atoi(&tmp[6 + ft_num_size(g_new_part.x)]);
		g_newfigure = (int32_t **)ft_matrixalloc(100, 100, sizeof(int32_t));
		part_definition();
		free(tmp);
	}
}


static void fillit_parser(int fd)
{
	char	*line;
	int		ret;
	int 	count;


	ret = 0;
	count = 2;
	while (get_next_line(fd1, &line))
	{
		ft_printf_fd(fd, "%-35s\t- %d\n", line, ret);
		if (ft_strstr(line, "$$$ exec p"))
		{
			first_line(line, fd);
			free(line);
		}
		else if (ft_strstr(line, "Plateau "))
		{
			map_scan(fd);
			get_next_line(fd1, &line);
			g_new_part.x = (int8_t)ft_atoi(&line[6]);
			g_new_part.y = (int8_t)ft_atoi(&line[6 + ft_num_size(g_new_part.x)]);
//			g_newfigure = (int32_t **)ft_matrixalloc(g_new_part.x, g_new_part.y, sizeof(int32_t));
			ft_printf_fd(fd, "part size %d:%d\n", g_new_part.x, g_new_part.y);
			free(line);
			part_definition();
		}
		ft_printf("%d %d\n", g_best_result.x, g_best_result.y);
		g_best_result.x = 0;
		g_best_result.y = 0;


//		if (!count--)
//		{
//			ft_printf_fd(fd, ">>> start  {%d:%d}\n>>> finish  {%d:%d}\n", g_friend_start.x, g_friend_start.y, g_friend_finish.x, g_friend_finish.y);
//			ft_printf("12 14\n");
//		}
	}
//	ft_printf_fd(fd, ">>> start  {%d:%d}\n>>> finish  {%d:%d}\n", g_friend_start.x, g_friend_start.y, g_friend_finish.x, g_friend_finish.y);
}

int		main()
{

//	if((fd1 = open("ttt.txt", O_RDONLY)) == -1)
//		return (22);
	fd1 = 0;
	fd = open("test.txt", O_RDWR, S_IRWXO);
	fillit_parser(fd);

	close(fd);
//	close(fd1);
	return (0);
}