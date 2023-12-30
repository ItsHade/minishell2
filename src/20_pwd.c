/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:46:45 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 18:46:47 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_pwd(t_envp *ep)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
	{
		cwd = ft_strdup(ft_getenv("PWD", ep));
		if (!cwd)
			return (-1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_do_chdir(char *t, t_envp **ep)
{
	char	*original_pwd;
	char	*cwd;

	cwd = NULL;
	original_pwd = ft_getenv("PWD", *ep);
	if (chdir(t) != 0)
		return (perror("chdir"), 1);
	cwd = getcwd(cwd, 0);
	if (do_export("OLDPWD", original_pwd, ep, NULL) == -1)
		return (-1);
	if (do_export("PWD", cwd, ep, NULL) == -1)
		return (-1);
	ft_free(cwd);
	return (0);
}	