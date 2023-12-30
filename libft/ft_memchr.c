/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:08:22 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/30 18:05:14 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{	
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char	*s = "hello";

	printf("%d", 1);
	//ft_memchr(NULL, 2+256, 3); //segment
	printf("%d", 2);
	//memchr(NULL,256 + 2, 3); //null error

	printf("%d", 3);
	//ft_memchr(s, 2+256, 3); //null

	printf("%d", 4);
	//memchr(s,256 + 2, 3); //error

	printf("%d", 5);
	
	int *p1 = ft_memchr(s, 'l', 3); //null

	printf("p1 = %p%d", p1, 6);
	int	*p2 = memchr(s,'l', 3); //error
	
	printf("P2 = %p\n%li\n", p2, sizeof(char));

	printf("%li\n", sizeof(int));
	printf("%li\n", sizeof(long int));
	printf("%li\n", sizeof(unsigned char));
	printf("%li\n", sizeof(unsigned int));
	return 0;
}*/
