/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:23:49 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/04 13:35:05 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_malloc(char **new, size_t j)
{
	while (j-- > 0)
		free(new[j]);
	free(new);
	return (NULL);
}

static size_t	n_word(char const *str, char c)
{
	size_t	i;
	size_t	s;
	size_t	n;

	i = 0;
	s = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != c && s == 0)
		{
			s++;
			n++;
		}
		if (str[i] == c)
			s = 0;
		i++;
	}
	return (n);
}

static char	**ft_newstr(char const *s, char c, char **new)
{
	int		start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < n_word(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		new[i] = ft_substr(s, start, j - start);
		if (new[i] == NULL)
			return (ft_free_malloc(new, i));
		i++;
	}
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;

	if (!s)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (n_word(s, c) + 1));
	if (new == NULL)
		return (NULL);
	new[n_word(s, c)] = 0;
	if (ft_newstr(s, c, new) == NULL)
		return (NULL);
	return (new);
}
