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

void	print_matr(int **matr, int fd)
{
	int i = 0, j;
	ft_printf_fd(fd, "\t  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  \n");
	while (i < g_x_max)
	{
		ft_printf_fd(fd, "%d\t{ ", i);
		j = 0;
		while (j < g_y_max)
		{
			ft_printf_fd(fd, "%d, ", matr[i][j]);
			j++;
		}
		i++;
		ft_printf_fd(fd, "}\n");
	}
	ft_printf_fd(fd, "MATRIX PRINTED\n");
}

int 	**map_scan(int fd)
{
	int	**matr;
//	char **map;
	int x = 0;
	char *tmp;
	int y;
	matr = (int **)ft_matrixalloc(g_x_max, g_y_max + 1, 1);
	ft_printf_fd(fd, "MATRIX START\n");
	get_next_line(0, &tmp);
	ft_printf_fd(fd, "%-35s\n", tmp);
	while (x < g_x_max && get_next_line(0, &tmp))
	{
		y    = 0;
		ft_printf_fd(fd, "%-35s\n", tmp);
		while (y < g_y_max + 4)
		{
//			ft_printf_fd(fd, " fail %d:%d\n", x, y);
			if (tmp[4 + y] == '.')
			{
				matr[x][y] = 0;
			}
			else if (tmp[4 + y] == 'O')
			{
				matr[x][y] = 5;
			}
			else
				matr[x][y] = 3;
			y++;
		}
		x++;
	}
	ft_printf_fd(fd, "MATRIX WRITEN\n");
	print_matr(matr, fd);
	return (matr);
}

static char	**fillit_parser(int x)
{
	char	*line;
	int		ret;
	int 	**map;
	int 	count;
	int fd;

	fd = open("test.txt", O_RDWR, S_IRWXO);

	ret = 0;
	count = x;
//	my = 0;
	while (count >= 0)
	{
		ret += get_next_line(0, &line);
		ft_printf_fd(fd, "%-35s\t- %d\n", line, ret);
		if (ft_strstr(line, "$$$ exec p"))
		{		if (line[10] == '1')
				g_dot = (char) 'o';
			else if (line[10] == '2')
				g_dot = (char) 'x';
		}
		else if (ft_strstr(line, "Plateau "))
		{
			g_x_max = ft_atoi(&line[7]);
			g_y_max = ft_atoi(&line[8 + ft_num_size(g_x_max)]);
			count = g_y_max;
			map = map_scan(fd);

		}
		else if (ft_strstr(line, "Piece "))
		{
			g_x_patr = ft_atoi(&line[6]);
			g_y_part = ft_atoi(&line[6 + ft_num_size(g_x_patr)]);
			count = g_y_part;
		}
		if (!count--)
		{
			ft_printf_fd(fd, "%c mapsize [%d]x[%d]\npart x%d y%d\n new %d\n", g_dot, g_x_max, g_y_max, g_x_patr, g_y_part, ret);
			ft_printf_fd(1, "12 14\n");
			count++;
		}
	}
	close(fd);
	return NULL;
}

int		main()
{

	char	**raw_map;


	raw_map = fillit_parser(2);
	return (0);
}