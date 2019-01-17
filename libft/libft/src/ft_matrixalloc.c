/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixalloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:18:39 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 13:52:09 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	**ft_matrixalloc(size_t width, size_t length, size_t buf)
{
	void	**matrix;
	size_t	n;

	n = 0;
	if (!(matrix = malloc(8 * width)))
		return (NULL);
	while (width-- > 0)
		if (!(matrix[n++] = malloc(length * buf)))
		{
			free(matrix);
			return (NULL);
		}
	return (matrix);
}
