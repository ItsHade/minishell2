/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:37:02 by yzhuang           #+#    #+#             */
/*   Updated: 2022/11/24 22:38:21 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <unistd.h>

void	ft_nbr(int n, int fd)
{
	int	t;

	if (n)
	{
		ft_nbr(n / 10, fd);
		t = n % 10 + '0';
		write(fd, &t, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n == 0)
			write (fd, "0", 1);
		if (n > 0)
			ft_nbr(n, fd);
		if (n < 0)
		{
			write (fd, "-", 1);
			ft_nbr(-n, fd);
		}
	}
}
/*
int	main(void)
{
ft_putnbr_fd(-5678899, 0);
return 0;
}*/
