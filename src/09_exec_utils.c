/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:32:44 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/31 17:56:27 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

void	ft_close_std(t_data *data)
{
	close(data->stdin);
	close(data->stdout);
}

void	error_msg(char *file, char *msg, int ret)
{
	char	*print;

	g_return = ret;
	print = ft_strjoin("minishell: ", file);
	if (!print)
		return ;
	print = ft_strjoinf(print, ": ");
	if (!print)
		return ;
	print = ft_strjoinf(print, msg);
	if (!print)
		return ;
	print = ft_strjoinf(print, "\n");
	if (!print)
		return ;
	ft_putstr_fd(print, 2);
	ft_free(print);
}

char	**ft_removepathprefix(char **paths)
{
	int	i;
	int	a;
	int	len;

	a = 5;
	i = 0;
	if (paths == NULL)
		return (NULL);
	len = ft_strlen(paths[0]);
	while (a < len)
	{
		paths[0][i] = paths[0][a];
		i++;
		a++;
	}
	paths[0][i] = '\0';
	return (paths);
}

char	**ft_getpaths(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = ft_split(envp[i], ':');
			if (!paths)
				return (NULL);
		}
		i++;
	}
	paths = ft_removepathprefix(paths);
	return (paths);
}

char	*ft_findcmdpath(char *cmd, char **envp, char *tmp, char *cmd_path)
{
	int		i;
	char	**paths;

	i = -1;
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0
		&& !ft_is_directory(cmd))
		return (ft_strdup(cmd));
	paths = ft_getpaths(envp);
	if (!paths)
		return (ft_strdup(cmd));
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freetab(paths), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (ft_freetab(paths), free(tmp), NULL);
		free(tmp);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (ft_freetab(paths), cmd_path);
		free(cmd_path);
	}
	return (ft_freetab(paths), ft_strdup(cmd));
}
