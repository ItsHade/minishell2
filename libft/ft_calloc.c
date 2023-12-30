/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:52:25 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/16 14:42:10 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*If there is an error, they return a NULL pointer and set errno to
     ENOMEM.*/

#include "libft.h"
//#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb > 0 && (size * nmemb) / nmemb != size)
		return (NULL);
	s = malloc(size * nmemb);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, size * nmemb);
	return (s);
}
