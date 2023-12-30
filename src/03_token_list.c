/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:21:24 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 11:21:26 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_lstnew(void *value)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (perror("ft_calloc"), NULL);
	new->value = value;
	new->label = EMPTY;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL || lst->next == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	cur = *lst;
	if (lst != NULL && *lst != NULL)
	{
		cur = ft_lstlast(*(lst));
		new->prev = cur;
		cur->next = new;
		return ;
	}
	*lst = new;
}

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;
	t_token	*start;

	start = *lst;
	while (start)
	{
		tmp = start->next;
		if (start->value != NULL)
			free(start->value);
		start->value = 0;
		free(start);
		start = tmp;
	}
	*lst = NULL;
}

size_t	ft_lstsize(t_envp **lst)
{
	size_t	i;
	t_envp	*current;

	i = 0;
	current = *lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
