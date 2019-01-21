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

static void	print_matr(double **matr, int fd)
{
	int i = 0, j;
	ft_printf_fd(fd, "\t   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5  6\n");
	while (i < g_mapsize[0])
	{
		ft_printf_fd(fd, "%d\t{ ", i);
		j = 0;
		while (j < g_mapsize[1] && **matr)
		{
			ft_printf_fd(fd, "%4.f", g_field[i][j]);
			j++;
		}
		i++;
		ft_printf_fd(fd, "}\n");
	}
	ft_printf_fd(fd, "MATRIX PRINTED\n");
}

long long	ft_abs(long long num)
{
	return num >= 0 ? num : -num;
}


static double			mesure_distance(int ax, int ay, int bx, int by)
{
	return (sqrt((double)((ax - bx) * (ax - bx) + (ay - by) * (ay - by))));
}
void		mark_field(int x, int y)
{
	int	i;
	int	j;
	int current;

	i = 0;
	while (i < g_mapsize[0])
	{
		j = 0;
		while (j < g_mapsize[1])
		{

			if (((g_field[i][j] > (current = mesure_distance(i + 1, j + 1, x + 1, y + 1))) && g_field[i][j] > 0) || g_field[i][j] == 0)
			{
				g_field[i][j] = current;
				j++;
			}
//			else if (g_field[i][j] >= 0)
//				j += y;
//			else
				j++;
		}
		i++;
	}
//	print_matr(g_field, fd);

}

double 		**map_scan(int fd)
{
	int x = 0;
	char *tmp;
	int y;
	int new_enemyes;

	new_enemyes = 0;
	get_next_line(0, &tmp);
	free(tmp);
	ft_printf_fd(fd, "<<< %-35s\n", tmp);

	while (x < g_mapsize[0] && get_next_line(0, &tmp))
	{
		y = 0;
		ft_printf_fd(fd, "%-35s\n", tmp);
		while (y < g_mapsize[1])
		{
			if (tmp[4 + y] == 'O' || tmp[4 + y] == 'o')
			{
				g_field[x][y] = ENEMY;
				mark_field(x, y);
			}

			else if (tmp[4 +  y] == 'X' || tmp[4 + y] == 'x')
				g_field[x][y] = FRIEND;
			y++;
		}
		x++;
		free(tmp);
	}
	ft_printf_fd(fd, "MATRIX WRITEN\n");
	print_matr(g_field, fd);
	return (g_field);
}

void		first_line(char *line, int fd)
{
	char	*tmp;
	if (line[10] == '1')
		g_dot = (char) 'o';
	else if (line[10] == '2')
		g_dot = (char) 'x';
	get_next_line(0, &tmp);
	if (ft_strstr(tmp, "Plateau "))
	{
		g_mapsize[0] = ft_atoi(&tmp[7]);
		g_mapsize[1] = ft_atoi(&tmp[8 + ft_num_size(g_mapsize[0])]);
		g_field = (double **)ft_matrixalloc(g_mapsize[0], g_mapsize[1], sizeof(double));
		ft_printf_fd(fd, "MATRIX ALLOCATED\n");
		ft_printf_fd(fd, "MATRIX START\n gxm - %d, gym - %d\n", g_mapsize, g_mapsize[1]);
		print_matr(g_field, fd);
		g_field = map_scan(fd);
	}
}

static char	**fillit_parser(int fd)
{
	char	*line;
	int		ret;
	int 	count;


	ret = 0;
	count = 2;
	while (count >= 0)
	{
		ret += get_next_line(0, &line);
		ft_printf_fd(fd, "%-35s\t- %d\n", line, ret);
		if (ft_strstr(line, "$$$ exec p"))
			first_line(line, fd);
		else if (ft_strstr(line, "Plateau "))
			g_field = map_scan(fd);
		else if (ft_strstr(line, "Piece "))
		{
			g_patr[0] = ft_atoi(&line[6]);
			g_patr[1] = ft_atoi(&line[6 + ft_num_size(g_patr[0])]);
			count = g_patr[1];
		}
		if (!count--)
		{
			ft_printf_fd(fd, "%c mapsize [%d]x[%d]\npart x%d y%d\n new %d\n", g_dot, g_mapsize[0], g_mapsize[1], g_patr[0], g_patr[1], ret);
			ft_printf_fd(1, "12 14\n");
			count++;
		}
	}

	return NULL;
}

int		main()
{

	fd = open("test.txt", O_RDWR, S_IRWXO);
	fillit_parser(fd);
	close(fd);
	return (0);
}