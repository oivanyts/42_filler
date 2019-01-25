
void	print_matr(float **matr, int8_t matr_x, int8_t matr_y)
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
