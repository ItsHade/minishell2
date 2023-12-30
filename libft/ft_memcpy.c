/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:58:01 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/24 16:39:20 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
     The memcpy() function copies n bytes from memory area src to memory
 area dst.  If dst and src
     overlap, behavior is undefined.  Applications in which dst and 
src might overlap should use
     memmove(3) instead.

RETURN VALUES
     The memcpy() function returns the original value of dst. */

#include "libft.h"
//#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == src || n == 0)
		return (dest);
	if (!dest && !src)
		return (0);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	de[3];	//ça marche c normal?
	char	sc[ ] = "abcd";
	size_t n = 6;

	ft_memcpy(de, sc, n);
	printf("%s", de);
	return 0;
}*/
