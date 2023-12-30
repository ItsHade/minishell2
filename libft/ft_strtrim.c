/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:41:43 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/24 22:49:19 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
*/

size_t	isset(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	n;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && isset(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && isset(set, s1[j - 1]))
			j--;
	new = malloc(sizeof(*s1) * (j - i + 1));
	if (!new)
		return (NULL);
	n = 0;
	while (s1[i] && i < j)
		new[n++] = s1[i++];
	new[n] = '\0';
	return (new);
}
/*#include <stdio.h>
int	main(void)
{
	char	*new = ft_strtrim(" 	--this is new--		", "	- ");
	printf("%s", new);
	free(new);
	
	//printf("%zu\n", ft_strlen("----              csc har         "));
	//printf("%zu\n", isset(".	- ", '	'));

	//printf("%zu", memlen("----	,	csc har 	-", "-	, "));
	return (0);
}*/
