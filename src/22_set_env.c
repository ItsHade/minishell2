/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:16:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 20:17:15 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_shell_level(t_envp **ep)
{
	int		shlvl;
	char	*s_lvl;
	char	*tmp;

	tmp = ft_getenv("SHELL", *ep);
	if (!tmp)
		return (-1);
	if (ft_strcmp(tmp, "minishell") != 0)
		return (-1);
	tmp = ft_getenv("SHLVL", *ep);
	if (!tmp)
		return (-1);
	shlvl = ft_atoi(tmp);
	shlvl++;
	s_lvl = ft_itoa(shlvl);
	if (!s_lvl)
		return (-1);
	do_export("SHLVL", s_lvl, ep, NULL);
	free(s_lvl);
	return (0);
}

int	set_empty_env(t_envp **ep)
{
	char	*s;

	s = NULL;
	s = ft_strjoin("PWD=", getcwd(s, 1024));
	if (!s)
		return (perror("ft_calloc"), ft_fail_alloc(), -1);
	if (add_new_envp(ep, split_env(s)) == -1)
		return (-1);
	free(s);
	s = ft_strdup("SHLVL=1");
	if (!s)
		return (perror("ft_calloc"), ft_fail_alloc(), -1);
	if (add_new_envp(ep, split_env(s)) == -1)
		return (-1);
	free(s);
	return (0);
}

int	set_env(t_envp **ep, char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL || envp[0] == NULL)
	{
		if (set_empty_env(ep) == -1)
			return (-1);
	}
	while (envp[i])
	{
		if (add_new_envp(ep, split_env(envp[i])) == -1)
			return (-1);
		i++;
	}
	if (ft_get_shell_level(ep) == 0)
		do_export("SHELL", "minishell", ep, NULL);
	return (0);
}
