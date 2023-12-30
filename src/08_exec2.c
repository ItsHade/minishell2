/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_exec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:18:29 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:18:35 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	ft_exec_abs(char **command, char **envp)
{
	ft_putstr_fd("is abso!\n", 2);
	if (execve(command[0], command, envp) == -1)
	{
		if (access(command[0], F_OK | X_OK) == 0)
		{
			ft_putstr_fd("@\n", 2);
			error_msg(command[0], ISDIR, 126);
			ft_freetab(envp);
			return (g_return);
		}
		ft_putstr_fd("#\n", 2);
		error_msg(command[0], NFOUND, 127);
		ft_freetab(envp);
		return (g_return);
	}
	return (0);
}

int	ft_is_absolute(char *cmd)
{
	struct stat	filestat;

	if (stat(cmd, &filestat) == 0)
	{
		if (filestat.st_mode & S_IXUSR)
			return (1);
		ft_putstr_fd("1\n", 2);
		if (filestat.st_mode & S_IFDIR)
			return (0);
		ft_putstr_fd("2\n", 2);
		// if (filestat.st_mode & S_IXOTH)
		// 	return (2);
		// ft_putstr_fd("3\n", 2);
		if (filestat.st_mode & S_IFREG & S_IXUSR)
			return (0);
		else if (filestat.st_mode & S_IFREG)
			return (1);
	}
	ft_putstr_fd("4\n", 2);
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
		return (ft_putstr_fd("YEP\n", 2), 2);
	return (-1);
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
