/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:04:06 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 14:52:21 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
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

	i = 'd';
	printf("%c", ft_toupper(i));
	return 0;
}
*/
