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

void	ft_jump_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\f'
			|| str[*i] == '\n' || str[*i] == '\r'
			|| str[*i] == '\t' || str[*i] == '\v'))
	(*i)++;
}

long	ft_atol(const char *str, int *too_big)
{
	int				sign;
	int				i;
	unsigned long	res;

	sign = 1;
	i = 0;
	res = 0;
	ft_jump_whitespace(str, &i);
	if (str[i] && str[i] == '+')
		i++;
	else if (str[i] && str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if ((res > LONG_MAX && sign == 1) || res - 1 > LONG_MAX)
		{
			*too_big = 1;
			return (0);
		}
	}
	return (res * sign);
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
