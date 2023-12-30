/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:01:55 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/22 17:01:57 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_return = 0;

char	*ft_get_line(t_data *data, char *line)
{
	line = readline("\033[4;32mMinishell\033[0;32m>\033[0;37m ");
	if (line != NULL)
	{
		if (line && *line)
			add_history(line);
		if (line[0] == '\0')
		{
			free(line);
			return (NULL);
		}
		if (quote_error(line))
			return (NULL);
		return (line);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		clear_ep(&data->env);
		rl_clear_history();
		exit(g_return);
	}
}

int	minishell(t_data *data)
{
	t_token	*token_list;

	token_list = NULL;
	while (1)
	{
		if (g_return == -1)
			ft_exit(data, NULL, -1);
		signal(SIGINT, ft_signal);
		signal(SIGQUIT, SIG_IGN);
		data->line = ft_get_line(data, data->line);
		if (ft_lexer(&token_list, &data->line, data) == -1)
			ft_exit(data, data->line, -1);
		if (!data->line)
			continue ;
		ft_free(data->line);
		if (syntax_error(&token_list))
			continue ;
		if (ft_parsing(&token_list, data) == -1)
			continue ;
		ft_lstclear(&token_list);
		if (ft_execute(data, &data->env) == -1)
			g_return = -1;
		ft_freecmdtable(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = NULL;
	set_env(&data.env, envp);
	minishell(&data);
	return (0);
}
