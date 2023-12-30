/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:51:18 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 16:55:40 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] > p2[i])
			return (1);
		if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*s = "salut";
	char	*s2 = "salt";

	printf("%d\n", ft_memcmp(s,s2, 4));
	printf("%d", memcmp(s,s2, 4));

	return 0;
}
*/
