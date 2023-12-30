/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:13:17 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 20:22:38 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}*/

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
#include <string.h>
#include<stdio.h>
int	main(void)
{
	printf("%s", ft_strdup("dfdf66"));
printf("%s", strdup("dfdf66"));
	 free(ft_strdup("dfdf66"));
	 free(strdup("dfdf66"));
return 0;
}
*/
