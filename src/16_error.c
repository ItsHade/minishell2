/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:11:25 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 13:12:43 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

void	ft_exit(t_data *data, char *line, int nb)
{
	clear_ep(&data->env);
	rl_clear_history();
	ft_free(line);
	line = NULL;
	exit(nb);
}

void	ft_error(char *s, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	perror(err);
}

void	ft_fail_alloc(void)
{
	g_return = -1;
}
