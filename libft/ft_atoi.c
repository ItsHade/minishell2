/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:00:34 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/16 14:50:27 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		s;
	long	res;

	s = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
			|| *str == '\t' || *str == '\v'))
		str++;
	if (*str && *str == '+')
		str++;
	else if (*str && *str == '-')
	{
		s *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (s < 0)
		res = -res;
	return (res);
}
/*
 #include <stdlib.h>
#include<stdio.h>
int	main(void)
{
	printf("%d\n", ft_atoi(" -+99999"));
	printf("%d\n",atoi("  -+99999"));
		printf("%d\n", ft_atoi(" -----99999"));
	printf("%d\n",atoi("  -----99999"));
		printf("%d\n", ft_atoi(" +-99999"));
	printf("%d\n",atoi("  +-99999"));
	printf("%d\n", ft_atoi(" -99999b"));
	printf("%d\n",atoi("  -99999b"));
	return (0);
}
*/
