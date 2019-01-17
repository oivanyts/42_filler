/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:15:54 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/07 14:18:42 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fresh;

	if (!lst || !f)
		return (NULL);
	if (lst->next)
	{
		fresh = ft_lstmap(lst->next, f);
		ft_lstadd(&fresh, f(lst));
	}
	else
		fresh = f(lst);
	return (fresh);
}
