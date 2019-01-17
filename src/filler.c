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

#define WRT write(fd, line, ft_strlen(line));

int main()
{
	char	*line;
	int		ret;
	char 	my;
//	char 	*mapsize;
	int 	count = 99;

	int fd = open("test.txt", O_CREAT | O_RDWR);
	ret = get_next_line(0, &line);
	WRT
	write(fd, "\n", 1);
	if (ft_strcmp(line, "$$$ exec p1 : [./bot.filler]"))
		my = 'x';
	else
		my = 'y';
	free(line);
	ret += get_next_line(0, &line);
//	mapsize = line;
	WRT
	while (ret += get_next_line(0, &line))
	{
		ft_putnbr_fd(ret, fd);
		write(fd, "\t", 1);
		WRT
		write(fd, "\n", 1);
		if (!ft_strncmp(line, "Piece ", 6))
			count = ft_atoi(&line[5]);
		if (!count--)
		{
			write(1, "8 2\n", 6);
		}
	}
	close(fd);
	return (0);
}