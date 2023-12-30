/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:27:19 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/30 12:40:59 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char	*s = "00  dfffj e";
	int	c= 0;
	printf("%s", ft_strchr(s,c));
	printf("%s", strchr(s,c));
	return 0;
}
*/
