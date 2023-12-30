/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:26:04 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 14:53:58 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
		return (c);
	}
	else
		return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	int	i;

	i = 'S';
	printf("%c", ft_tolower(i));

	return 0;
}
*/
