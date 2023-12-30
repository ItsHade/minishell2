/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:19:45 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 15:50:24 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stddef.h>
#include "libft.h"
/*
size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ph;

	i = 0;
	ph = (char *) haystack;
	if (ft_strlen(needle) == 0 || haystack == needle)
		return (ph);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			while (needle[j] && haystack[i + j] && (i + j < len)
				&& (needle[j] == haystack[i + j]))
				j++;
			if (j == ft_strlen(needle))
				return (ph + i);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	*s = "salut,ca va ca va?";
	char	*s2 = "alut,ca va";

	printf("%p\n", ft_strnstr(s,s2, 14));
	printf("%p\n", strnstr(s,s2, 14));
	printf("%p", s);
	return 0;
}
*/
