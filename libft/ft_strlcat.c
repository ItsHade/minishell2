/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:37:34 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 14:40:34 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lens;
	size_t	lend;

	j = 0;
	lens = ft_strlen(src);
	lend = ft_strlen(dst);
	i = lend;
	if (size == 0)
		return (lens);
	if (size < lend)
		return (lens + size);
	else
	{
		while (src[j] && ((lend + j) < size))
			dst[i++] = src[j++];
		if (((lend + j) == size) && (lend < size))
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (lens + lend);
	}
}
/*
#include <stdio.h>
//#include <bsd/string.h>
#include <string.h>

int    main(void)
{
    const char    srcf[8] = "bonjour";
char destf[5] = "cavat";

const char    src[8] = "bonjour";
char dest[5] = "cavat";

    printf("%zu\n", ft_strlcat(destf, srcf, 5));
  printf("%zu\n", strlcat(dest, src, 5));
    return (0);
}
*/
