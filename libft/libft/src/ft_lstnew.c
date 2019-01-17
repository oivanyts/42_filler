/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:27:07 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 11:56:13 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;
	void	*tmp;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		lst->content_size = 0;
		tmp = NULL;
	}
	else
	{
		if (!(tmp = malloc(content_size)))
		{
			free(lst);
			return (NULL);
		}
		ft_memcpy(tmp, content, content_size);
		lst->content_size = content_size;
	}
	lst->next = NULL;
	lst->content = tmp;
	return (lst);
}
