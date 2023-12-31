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
	g_return = ret;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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
	char	**command;

	i = -1;
	paths = ft_getpaths(envp);
	if (!paths)
		return (NULL);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (ft_freetab(paths), NULL);
	if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0 && !ft_is_directory(cmd))
	{
		cmd_path = ft_strdup(command[0]);
		return (ft_freetab(paths), ft_freetab(command), cmd_path);
	}
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freetab(paths), ft_freetab(command), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (ft_freetab(paths), ft_freetab(command), free(tmp), NULL);
		free(tmp);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (ft_freetab(paths), ft_freetab(command), cmd_path);
		free(cmd_path);
	}
	return (ft_freetab(paths), ft_freetab(command), ft_strdup(cmd)); //NULL
}
