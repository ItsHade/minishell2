/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:50:25 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 18:50:26 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envp	*ft_lstlast_ev(t_envp *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_ev(t_envp **lst, t_envp *new)
{
	t_envp	*t;

	t = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		t = ft_lstlast_ev(*lst);
		t->next = new;
	}
}

char	*ft_getenv(char *env_name, t_envp *ep)
{
	while (ep)
	{
		if (!(ft_strcmp(ep->content[0], env_name)))
			return (ep->content[1]);
		ep = ep->next;
	}
	return (NULL);
}

void	print_export(t_envp *ep)
{
	if (!ep)
		return ;
	while (ep)
	{
		printf("declare -x ");
		if (ep->content[0])
			printf("%s", ep->content[0]);
		if (ep->content[1])
			printf("=\"%s\"\n", ep->content[1]);
		else
			printf("\n");
		ep = ep->next;
	}
}
