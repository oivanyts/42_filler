/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:56:49 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/06 17:57:00 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char		*ft_words_st(const char *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	if (!(word = (char *)malloc(sizeof(char) * ft_countletter(s, c) + 1)))
		return (NULL);
	while (*s != c && *s)
		word[i++] = *s++;
	word[i] = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	word;

	word = 0;
	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	if (!(arr = (char **)malloc(sizeof(char *) * ft_countwords(s, c) + 2)))
		return (NULL);
	while (*s)
	{
		if (*s != c && *s)
		{
			arr[word++] = ft_words_st(s++, c);
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	arr[word] = NULL;
	return (arr);
}
