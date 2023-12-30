/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:44:07 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/30 20:58:45 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}
*/
char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
/*#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char	*s = "hello";
	int	c= 0;
	printf("====%s======\n", ft_strrchr(s,c));
	printf("=====%s=====", strrchr(s,c));
	return 0;
}
*/
