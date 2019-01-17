/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 11:02:51 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/24 11:26:30 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char		*addin_to_string(char **str, void *to_add, size_t size_to_add)
{
	char *tmp;

	if (!*str)
		tmp = ft_memalloc(size_to_add + 1);
	else
	{
		tmp = ft_memalloc(ft_strlen(*str) + size_to_add + 1);
		tmp = ft_strncpy(tmp, *str, ft_strlen(*str));
	}
	free(*str);
	if (!size_to_add)
		return (tmp);
	ft_memcpy(tmp + ft_strlen(tmp), to_add, size_to_add);
	return (tmp);
}

static int		find_line_end(void *str, size_t size)
{
	int		n;
	char	*tmp;

	tmp = (char *)str;
	n = -1;
	while (++n < (int)size)
	{
		if (tmp[n] == '\n')
			return (n);
	}
	return (-1);
}

static t_list	*search_fd(const int fd, t_list **list)
{
	t_list	*new_node;
	t_list	*crawler;

	if (*list)
	{
		crawler = *list;
		while (crawler)
		{
			if (crawler->content_size == (size_t)fd)
				return (crawler);
			crawler = crawler->next;
		}
	}
	new_node = ft_lstnew(NULL, 0);
	new_node->content_size = (size_t)fd;
	ft_lstadd(list, new_node);
	return (*list);
}

static void		*write_line(char *str, char **line, size_t len_str, int to_free)
{
	void	*next;

	if (!ft_memchr(str, '\n', len_str))
	{
		*line = addin_to_string(&*line, str, ft_strlen(str));
		if (to_free)
			free((void *)str);
		return (NULL);
	}
	else
	{
		*line = addin_to_string(&*line, str,
								(size_t)find_line_end(str, len_str));
		if (BUFF_SIZE > 1)
			next = ft_strdup(ft_memchr(str, '\n', len_str) + 1);
		else
			next = ft_strnew(0);
		free((void *)str);
		return (next);
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*tmp_list;
	t_list			*cur;
	char			*buf;
	int				status;

	if (fd < 0 || !line)
		return (-1);
	cur = search_fd(fd, &tmp_list);
	*line = ft_strnew(0);
	if (cur->content &&
	(cur->content = write_line(cur->content, line, ft_strlen(cur->content), 1)))
		return (1);
	buf = ft_strnew(BUFF_SIZE);
	while (0 < (status = (int)read(fd, buf, BUFF_SIZE)))
	{
		if ((cur->content = write_line(buf, line, (size_t)status, 0)))
			return (1);
		ft_bzero(buf, (size_t)status);
	}
	free((void *)buf);
	if (status < 0)
		return (-1);
	return (**line != 0);
}
