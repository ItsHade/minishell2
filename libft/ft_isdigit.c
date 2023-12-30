/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:58:18 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/15 11:27:56 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	int	i;

	i = '7';
	printf("%d", ft_isdigit(i));
	return (0);
}
*/
/*The isnumber() function behaves similarly to isdigit(), but
 may recognize additional characters,
     depending on the current locale setting.

     The value of the argument must be representable as an
 unsigned char or the value of EOF.*/
