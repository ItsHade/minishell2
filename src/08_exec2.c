/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_exec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:18:29 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/31 18:20:18 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	ft_is_directory(char *cmd)
{
	struct stat	filestat;

	if (stat(cmd, &filestat) == 0)
	{
		if (filestat.st_mode & S_IFDIR)
			return (1);
	}
	return (0);
}

int	ft_execve_error(char *cmd)
{
	//
	fprintf(stderr, "errno: %d\n", errno);
	if (errno == EACCES && ft_is_directory(cmd))
		error_msg(cmd, ISDIR, 126);
	else if (errno == EACCES)
		error_msg(cmd, PERM, 126);
	else if (errno == ENOENT && ft_is_directory(cmd))
		error_msg(cmd, NOFILE, 127);
	else
		error_msg(cmd, NFOUND, 127);
	return (0);
}

int	ft_get_return_value(t_data *data)
{
	int	return_pid;
	int	i;

	i = -1;
	while (++i < data->nb_cmd)
	{
		return_pid = waitpid(0, &data->status, 0);
		if (return_pid == -1)
			return (-1);
		if (return_pid == data->pid && data->pid > 0)
		{
			if (data->status == 2)
			{
				ft_putstr_fd("\n", 2);
				g_return = 130;
			}
			else if (data->status >= 256)
				g_return = (data->status / 256);
			else
				g_return = (data->status % 256 + 256) % 256;
		}
	}
	if (g_return == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (0);
}

int	ft_exec_cmd(t_data *data, t_envp **envp, int i)
{
	while (i < data->nb_cmd)
	{
		ft_expand_cmd(data, envp, i);
		ft_expand_files(data, envp, i);
		if (ft_is_builtin(data, i) == 1)
		{
			if (ft_exec_builtin(data, envp, i) == -1)
				return (-1);
		}
		else
		{
			if (ft_do_cmd(data, envp, i) == -1)
				return (-1);
		}
		i++;
	}
	ft_get_return_value(data);
	i = -1;
	while (++i < data->nb_cmd)
		ft_unlink_here_doc(data, i);
	return (0);
}

int	ft_execute(t_data *data, t_envp **envp)
{
	int	i;

	i = 0;
	data->status = 0;
	data->pid = -1;
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	if (ft_check_here_doc(data, -1) == -1)
		return (ft_close_std(data), -1);
	if (ft_exec_cmd(data, envp, i) == -1)
		return (ft_close_std(data), -1);
	if (dup2(data->stdin, STDIN_FILENO) == -1)
		return (perror("dup2"), ft_close_std(data), -1);
	if (dup2(data->stdout, STDOUT_FILENO) == -1)
		return (perror("dup2"), ft_close_std(data), -1);
	ft_close_std(data);
	return (0);
}
