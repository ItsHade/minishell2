/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:38:05 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 11:38:10 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	ft_closepipe(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	ft_open_here_doc(t_data *data, int i)
{
	char	*file;
	char	*nb;

	file = NULL;
	nb = ft_itoa(i);
	if (!nb)
		return (-1);
	file = ft_strjoin("/tmp/.here_doc", nb);
	free(nb);
	if (!file)
		return (-1);
	data->infile = open(file, O_RDONLY, 00644);
	free(file);
	if (data->infile < 0)
		return (ft_error(NULL, file), -1);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		return (close(data->infile), -1);
	close(data->infile);
	return (g_return);
}

int	ft_open_output_file(t_data *data, char *file, int mode)
{
	if (mode == O_RDR)
	{
		data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (data->outfile < 0)
			return (ft_error(NULL, file), -1);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			return (close(data->outfile), -1);
		close(data->outfile);
	}
	else if (mode == OAPPEND)
	{
		data->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (data->outfile < 0)
			return (ft_error(NULL, file), -1);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			return (close(data->outfile), -1);
		close(data->outfile);
	}
	return (0);
}

int	ft_open_file(t_data *data, char *file, int mode, int i)
{
	if (mode == I_RDR)
	{
		data->infile = open(file, O_RDONLY, 00644);
		if (data->infile < 0)
			return (ft_error(NULL, file), -1);
		if (dup2(data->infile, STDIN_FILENO) == -1)
			return (close(data->infile), -1);
		close(data->infile);
	}
	else if (mode == OAPPEND || mode == O_RDR)
		return (ft_open_output_file(data, file, mode));
	else if (mode == HEREDOC)
		return (ft_open_here_doc(data, i));
	return (0);
}

int	ft_io_file(t_data *data, t_envp **envp, int i, int is_pipe)
{
	int	a;

	a = -1;
	while (++a < data->commands[i].nb_io)
	{
		if (data->commands[i].files[a] == NULL)
			return (error_msg(data->commands[i].files[a], AMBIGUOUS, 1), 1);
		else if (data->commands[i].is_ambiguous[a] == 1)
			return (error_msg(data->commands[i].files[a], AMBIGUOUS, 1), 1);
		else if (ft_open_file(data, data->commands[i].files[a],
				data->commands[i].redir[a], i) == -1)
		{
			if (is_pipe == 1)
			{
				ft_freecmdtable(data);
				clear_ep(envp);
				g_return = 1;
				exit (g_return);
			}
			g_return = 1;
			return (g_return);
		}
	}
	return (0);
}
