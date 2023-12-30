/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:57:33 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 19:15:55 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

t_exp	*ft_lstlast_exp(t_exp *lst)
{
	if (lst == NULL || lst->next == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_exp(t_exp **lst, t_exp *new)
{
	t_exp	*cur;

	cur = *lst;
	if (lst != NULL && *lst != NULL)
	{
		cur = ft_lstlast_exp(*(lst));
		cur->next = new;
		return ;
	}
	*lst = new;
}

void	clear_exp(t_exp **exp)
{
	t_exp	*t;

	t = NULL;
	if (exp)
	{
		while (*exp)
		{
			if ((*exp)->next)
				t = (*exp)->next;
			ft_free((*exp)->s);
			(*exp)->s = NULL;
			ft_free(*exp);
			*exp = NULL;
			*exp = t;
			t = NULL;
		}
	}
	*exp = NULL;
}

int	add_new_exp(t_exp **exp, char *str)
{
	t_exp	*new_exp;

	new_exp = malloc(sizeof(t_exp));
	if (!new_exp)
	{
		perror("Malloc failed in add_new_exp");
		clear_exp(exp);
		g_return = -1;
		return (-1);
	}
	new_exp->s = str;
	new_exp->next = NULL;
	ft_lstadd_back_exp(exp, new_exp);
	return (0);
}

void	print_exp(t_exp *exp)
{
	if (!exp)
		return ;
	while (exp)
	{
		if (exp->s)
			ft_putstr_fd(exp->s, 1);
		exp = exp->next;
	}
}
