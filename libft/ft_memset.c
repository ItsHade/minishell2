/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:12 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/24 16:32:36 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
     The memset() function writes len bytes of value c (converted 
to an unsigned char) to the string b.

RETURN VALUES
     The memset() function returns its first argument.*/

#include "libft.h"
//#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pb;

	if (!b)
		return (NULL);
	pb = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		pb[i] = c;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[6] = "idokf";
	
	ft_memset(str, 'c', sizeof(char) *2);
	//memset(str, 'c', sizeof(char) *2);
	for (int i = 0; i < 6; i++) 
		printf("%c",  str[i]);
	return 0;
}*/
