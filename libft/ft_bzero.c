/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:17:43 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 12:04:13 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <strings.h>
DESCRIPTION
     The bzero() function writes n zeroed bytes to the string s.  
If n is zero, bzero() does
     nothing.  */

#include "libft.h"
//#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ps;

	ps = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		ps[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[6] = "oui,ok";

	//ft_bzero(str, 2);
	bzero(str, 2);
	for (int i = 0; i < 6; i++)
		printf("%c",  str[i]);
	return 0;
}
*/
