/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:34:48 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 20:19:58 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	ft_do_builtin(t_data *data, t_envp **envp, int i, int is_pipe)
{
	if (ft_strcmp(data->commands[i].cmd_arg[0], "echo") == 0)
		return (do_echo(&data->commands[i]));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "cd") == 0)
		return (exec_cd(&data->commands[i], envp));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "pwd") == 0)
		return (do_pwd(*envp));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "export") == 0)
		return (do_exports(&data->commands[i], envp, 0));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "unset") == 0)
		return (do_unsets(&data->commands[i], envp));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "env") == 0)
		return (print_envp(*envp));
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "exit") == 0)
		return (do_exit(data, envp, i, is_pipe));
	return (0);
}

int	ft_is_builtin(t_data *data, int i)
{
	if (data->commands[i].cmd_arg[0] == NULL)
		return (0);
	if (ft_strcmp(data->commands[i].cmd_arg[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "export") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "env") == 0)
		return (1);
	else if (ft_strcmp(data->commands[i].cmd_arg[0], "exit") == 0)
		return (1);
	return (0);
}

int	ft_builtin_child(t_data *data, t_envp **envp, int i)
{
	if (i != data->nb_cmd - 1)
	{
		if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
			return (ft_closepipe(data->pipefd), -1);
	}
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	g_return = ft_io_file(data, envp, i, 1);
	g_return = ft_do_builtin(data, envp, i, 1);
	ft_freecmdtable(data);
	clear_ep(envp);
	exit (g_return);
	return (g_return);
}

int	ft_exec_builtin_pipe(t_data *data, t_envp **envp, int i)
{
	int	pid;

	if (pipe(data->pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (ft_closepipe(data->pipefd), perror("fork"), -1);
	if (pid == 0)
	{
		ft_close_std(data);
		if (ft_builtin_child(data, envp, i) == -1)
			return (-1);
	}
	else
	{
		if (i == data->nb_cmd - 1)
			data->pid = pid;
		if (i != data->nb_cmd - 1)
		{
			if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
				return (ft_closepipe(data->pipefd), exit(g_return), -1);
		}
		ft_closepipe(data->pipefd);
	}
	return (g_return);
}

int	ft_exec_builtin(t_data *data, t_envp **envp, int i)
{
	if (data->nb_cmd > 1)
		return (ft_exec_builtin_pipe(data, envp, i));
	if (ft_io_file(data, envp, i, 0) == 1)
		return (1);
	g_return = ft_do_builtin(data, envp, i, 0);
	return (g_return);
}
