/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:30:12 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:30:13 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_ep(t_envp *ep)
{
	ft_free(ep->content[0]);
	ep->content[0] = NULL;
	ft_free(ep->content[1]);
	ep->content[1] = NULL;
	ft_free(ep->content);
	ep->content = NULL;
	ft_free(ep);
	ep = NULL;
}

int	do_unsets(t_command *cmd, t_envp **ep)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!cmd->cmd_arg[1])
		return (0);
	while (cmd->cmd_arg[i] != NULL)
	{
		if (do_unset(cmd->cmd_arg[i], ep) == 1)
			ret = 1;
		i++;
	}
	return (ret);
}

int	ft_do_unset(char *arg, t_envp *t, t_envp *t2)
{
	while (t && t->next)
	{
		if (!(ft_strcmp(t->next->content[0], arg)))
		{
			if (t->next->next)
				t2 = t->next->next;
			ft_free_ep(t->next);
			t->next = t2;
		}
		t = t->next;
	}
	return (0);
}

int	do_unset(char *arg, t_envp **ep)
{
	t_envp	*t;
	t_envp	*t2;

	if (!(ft_strcmp(arg, "$?")))
		return (ft_putstr_fd(DOLQUESTION, 2), 1);
	if (!*ep)
		return (0);
	t = *ep;
	t2 = NULL;
	if (!(ft_strcmp((*ep)->content[0], arg)))
	{
		if (!(*ep)->next)
		{
			ft_free_ep((*ep));
			(*ep) = NULL;
		}
		else
		{
			t2 = (*ep)->next;
			ft_free_ep(*ep);
			*ep = t2;
		}
		return (0);
	}
	return (ft_do_unset(arg, t, t2));
}
