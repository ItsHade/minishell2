/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:42:15 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:42:25 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

void	ft_child_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		g_return = 130;
		exit(g_return);
	}
}

void	ft_here_doc_signal(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_return = -1;
	}
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_return = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
