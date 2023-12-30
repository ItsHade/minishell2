/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:13:47 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/29 16:37:19 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c])
		c++;
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "stgg dfd";
	
	printf("%zu", ft_strlen(str));
	return (0);
}
*/
