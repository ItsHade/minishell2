/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:13:02 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 13:19:25 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	print_envp(t_envp *envp)
{
	if (!envp)
		return (-1);
	while (envp)
	{
		if (envp->content[0] && envp->content[1])
			printf("%s=%s\n", envp->content[0], envp->content[1]);
		envp = envp->next;
	}
	return (0);
}

void	free_content(char **content)
{
	if (!content)
		return ;
	ft_free(content[0]);
	ft_free(content[1]);
	content[0] = NULL;
	content[1] = NULL;
	free(content);
}		

char	**split_env(char *s)
{
	int	i;
	int	tlen;

	i = 0;
	tlen = 0;
	if (s[0] == '=' || !s[0])
	{
		printf("Minishell: export: `%s': not a valid identifier\n", s);
		g_return = 1;
		return (NULL);
	}
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
	{
		tlen = ft_strlen(s) - i - 1;
		if (tlen)
			return (add_content(ft_substr(s, 0, i), ft_substr(s, i + 1, tlen)));
		else
			return (add_content(ft_substr(s, 0, i), NULL));
	}
	else
		return (add_content(ft_substr(s, 0, i), NULL));
}

int	add_new_envp(t_envp **ep, char **content)
{
	t_envp	*new_ep;

	new_ep = ft_calloc(sizeof(t_envp), 1);
	if (!new_ep)
	{
		perror("Malloc failed in add_new_ep");
		clear_ep(ep);
		g_return = -1;
		return (-1);
	}
	new_ep->content = content;
	new_ep->next = NULL;
	ft_lstadd_back_ev(ep, new_ep);
	g_return = 0;
	return (0);
}

void	clear_ep(t_envp **ep)
{
	t_envp	*t;
	int		i;

	t = NULL;
	while (*ep)
	{
		if ((*ep)->next)
			t = (*ep)->next;
		i = 0;
		while (i < 2)
		{
			ft_free((*ep)->content[i]);
			(*ep)->content[i] = NULL;
			i++;
		}
		ft_free((*ep)->content);
		ft_free(*ep);
		*ep = t;
		t = NULL;
	}
	ep = NULL;
}
