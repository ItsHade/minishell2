/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:35:56 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 11:35:58 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

// pipefd[0] read
// pipefd[1] write

// STDIN_FILENO		0	/* Standard input.  */
// STDOUT_FILENO	1	/* Standard output.  */
// STDERR_FILENO	2	/* Standard error output.  */

int	ft_unlink_here_doc(t_data *data, int i)
{
	int		nb_doc;
	char	*nb;
	char	*file;

	file = NULL;
	if (ft_is_here_doc(data, i, &nb_doc) < 1)
		return (0);
	nb = ft_itoa(i);
	if (!nb)
		return (-1);
	file = ft_strjoin("/tmp/.here_doc", nb);
	ft_free(nb);
	if (!file)
		return (-1);
	if (unlink(file) == -1)
		return (perror(file), -1);
	ft_free(file);
	return (0);
}

int	ft_here_doc2(char *limiter, int fd)
{
	char	*ptr;

	ptr = NULL;
	while (g_return != -1)
	{
		ptr = readline("> ");
		if (!ptr)
			return (0);
		if (ft_strcmp(ptr, limiter) == 0)
		{
			return (free(ptr), 0);
		}
		ptr = ft_strjoinf(ptr, "\n");
		if (!ptr)
			return (perror("malloc in strjoinf"), -1);
		ft_putstr_fd(ptr, fd);
		free(ptr);
	}
	return (0);
}

int	ft_here_doc(char *limiter, int i)
{
	int		fd;
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
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 00644);
	ft_free(file);
	if (fd < 0)
		return (perror(file), -1);
	signal(SIGINT, ft_here_doc_signal);
	signal(SIGQUIT, SIG_IGN);
	if (ft_here_doc2(limiter, fd) == -1)
		return (-1);
	close(fd);
	signal(SIGINT, ft_signal);
	return (0);
}

int	ft_is_here_doc(t_data *data, int i, int *nb_doc)
{
	int	a;

	*nb_doc = 0;
	a = 0;
	while (a < data->commands[i].nb_io)
	{
		if (data->commands[i].redir[a] == HEREDOC)
			(*nb_doc)++;
		a++;
	}
	return (*nb_doc);
}

int	ft_check_here_doc(t_data *data, int i)
{
	int		nb_doc;
	int		a;
	int		j;
	char	*limiter;

	while (++i < data->nb_cmd)
	{
		a = 0;
		j = -1;
		if (ft_is_here_doc(data, i, &nb_doc) < 1)
			continue ;
		while (++j < nb_doc)
		{
			while (data->commands[i].redir[a] != HEREDOC)
				a++;
			limiter = data->commands[i].files[a];
			if (!limiter)
				return (-1);
			if (ft_here_doc(limiter, i) == -1)
				return (-1);
			a++;
		}
	}
	return (g_return);
}
