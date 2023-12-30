/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:29:39 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:29:40 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_lst_to_tab(t_envp **lst)
{
	t_envp	*current;
	char	**tab;
	int		i;

	current = *lst;
	tab = NULL;
	i = 0;
	tab = ft_calloc(sizeof(char *), (ft_lstsize(lst) + 1));
	if (!tab)
		return (NULL);
	while (current)
	{
		tab[i] = ft_strjoin(current->content[0], "=");
		tab[i] = ft_strjoinf(tab[i], current->content[1]);
		current = current->next;
		i++;
	}
	return (tab);
}

char	*ft_strjoinf(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(*s1), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (ft_free(s1), perror("ft_calloc failed in strjoinf"), NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	ft_free(s1);
	return (new);
}

int	is_env(int c)
{
	if (ft_isalnum(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	inv_env_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(is_env(s[i])))
			return (1);
		i++;
	}
	return (0);
}
