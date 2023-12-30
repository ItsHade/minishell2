/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:30:49 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/29 14:51:23 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The string representing the integer.
NULL if the allocation fails.
Description
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.*/

#include "libft.h"
/*#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>*/

int	ilen(long int n)
{
	int	res;

	res = 0;
	if (n == 0)
		res = 1;
	if (n > 0)
	{
		while (n > 0)
		{
			n /= 10;
			res++;
		}
	}
	if (n < 0)
	{
		n = -n;
		while (n > 0)
		{
			n /= 10;
			res++;
		}
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			l;
	long int	nb;

	nb = n;
	l = ilen(nb);
	res = malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (n == 0)
		res[0] = '0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb >= 1)
	{
		res[l - 1] = nb % 10 + '0';
		nb /= 10;
		l--;
	}
	return (res);
}
/*
int	main(void)
{
	char	*s = (ft_itoa(-2147483648));
	printf("%d\n", ilen(-2345566));
	
	printf("%d\n", ilen(0));
	printf("%s", s);
	free(s);
	return 0;
}*/
