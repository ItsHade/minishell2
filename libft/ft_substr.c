/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:33:20 by yzhuang           #+#    #+#             */
/*   Updated: 2022/12/01 16:28:20 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <stddef.h>

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
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	mnlen;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	mnlen = ft_strlen(s) - start;
	if (len > mnlen)
		len = mnlen;
	new = malloc(sizeof(*s) * (len + 1));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = *(s + start + i);
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*#include <string.h>
#include<stdio.h>
int	main(void)
{
	char	*s = ft_substr("dfdf66", 100, 1);
	printf("%d",strcmp(s, ""));
	printf("%s", s);
	free(s);
return 0;
}*/
