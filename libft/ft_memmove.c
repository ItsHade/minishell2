/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:13:02 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/24 22:25:48 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <string.h>
#include <stddef.h>*/

void	ft_move2(char *d, char *s, size_t n, size_t i)
{
	if (d > s && d - s < (int)n)
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	else if (s > d && s - d < (int)n)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *) dest;
	s = (char *) src;
	i = 0;
	if (d == s || n == 0)
		return (dest);
	if (((s > d && s - d < (int)n)) || (d > s && d - s < (int)n))
	{
		ft_move2(d, s, n, i);
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	de[] = "abcdefgh";
	//char	sc[ ] = "abcd";
	//char *res;
	size_t n = 5;

	//ft_memmove(de + 2, de, n);
	memmove(de +2, de, n);
	printf("%s", de);
	return 0;
}*/
