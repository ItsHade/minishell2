/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:26:17 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 22:26:18 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_ab_path(char *path)
{
	char	*t;
	char	*filename;
	char	*cwd;

	cwd = NULL;
	t = NULL;
	filename = NULL;
	cwd = getcwd(cwd, 0);
	if (path[0] == '.' && path[1] == '/')
		filename = ft_substr(path, 1, ft_strlen(path) - 1);
	else
		filename = ft_strjoin("/", path);
	if (!filename)
		return (perror("malloc"), ft_fail_alloc(), NULL);
	t = ft_strjoinf(cwd, filename);
	free(filename);
	if (!t)
		return (NULL);
	cwd = NULL;
	return (t);
}

int	ft_get_path(char *path, char **t, t_envp *ep)
{
	if (path == NULL || (path[0] == '~' && (!path[1] || path[1] == '/')))
	{
		*t = ft_strdup(ft_getenv("HOME", ep));
		if (!(*t))
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if ((path[0] == '.' && path[1] == '/')
		|| (path[0] != '.' && path[0] != '/'))
		*t = get_ab_path(path);
	else
		*t = ft_strdup(path);
	if (!(*t))
		return (-1);
	return (0);
}

int	ft_open_dir(char *path, char *t)
{
	DIR	*dirp;

	dirp = opendir(t);
	if (!dirp)
	{
		if (access(path, F_OK) == 0)
			printf("minishell: cd : %s: Not a directory\n", path);
		else
			printf("minishell: cd : %s: No such file or directory\n", path);
		return (1);
	}
	closedir(dirp);
	return (0);
}

int	do_cd(char *path, t_envp **ep)
{
	char	*t;
	int		ret;

	t = NULL;
	ret = ft_get_path(path, &t, *ep);
	if (ret == -1 || ret == 1)
		return (ret);
	if (ft_open_dir(path, t) == 1)
		return (ft_free(t), 1);
	ret = ft_do_chdir(t, ep);
	ft_free(t);
	return (ret);
}

int	exec_cd(t_command *cmd, t_envp **ep)
{
	if (cmd->cmd_arg[1] == NULL)
		return (do_cd(NULL, ep));
	else if (cmd->cmd_arg[1] != NULL && cmd->cmd_arg[2] == NULL)
		return (do_cd(cmd->cmd_arg[1], ep));
	else if (cmd->cmd_arg[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
