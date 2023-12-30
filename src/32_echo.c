/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:12:16 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 19:13:12 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	is_option_n(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' && s[1] == 'n' )
	{
		i += 2;
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i])
			return (0);
	}
	else
		return (0);
	return (1);
}

int	do_echo(t_command *cmd)
{
	int	option_n;
	int	i;

	option_n = 0;
	i = 1;
	while (cmd->cmd_arg[i] != NULL)
	{
		if (!is_option_n(cmd->cmd_arg[i]))
			break ;
		else
			option_n = 1;
		i++;
	}
	while (cmd->cmd_arg[i] != NULL)
	{
		if (cmd->cmd_arg[i][0])
			ft_putstr(cmd->cmd_arg[i]);
		if (cmd->cmd_arg[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (!option_n)
		ft_putstr("\n");
	return (0);
}

int	add_exp_value(t_exp **exp, char *env_name, t_envp *ep)
{
	char	*env_value;
	char	*t;

	t = NULL;
	env_value = NULL;
	t = ft_getenv(env_name, ep);
	if (t)
		env_value = ft_strdup(t);
	if (env_value || env_name[0] == '?')
	{
		if (env_name[0] == '?')
		{
			t = ft_itoa(g_return);
			if (!t)
				return (-1);
		}
		else
			t = env_value;
		if (add_new_exp(exp, t) == -1)
			return (-1);
	}
	ft_free(env_name);
	return (0);
}
