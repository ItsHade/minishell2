/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:56:53 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 18:57:00 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	ft_expand_cmd(t_data *data, t_envp **env, int i)
{
	t_exp	*exp;
	int		a;

	a = 0;
	exp = NULL;
	if (data->commands[i].cmd_arg == NULL)
		return (0);
	while (data->commands[i].cmd_arg[a] != NULL)
	{
		if (do_quote_exp(&exp, data->commands[i].cmd_arg[a], *env, 1) == -1)
			return (-1);
		free(data->commands[i].cmd_arg[a]);
		if (!exp)
			data->commands[i].cmd_arg[a] = ft_strdup("");
		else
			data->commands[i].cmd_arg[a] = exp_to_str(exp);
		clear_exp(&exp);
		exp = NULL;
		if (!data->commands[i].cmd_arg[a])
			return (-1);
		a++;
	}
	return (0);
}

int	is_amb_cmd(char *t, t_envp *ep)
{
	int	dl;
	int	ret;

	dl = 0;
	while (t[dl] && t[dl] != '$')
		dl++;
	if (t[dl] != '$')
	{
		ft_free(t);
		return (0);
	}
	if (add_dollar_str(&t, dl, ep) == -1)
		return (-1);
	ret = check_amb_str(t);
	ft_free(t);
	return (ret);
}

int	ft_not_amb(t_command *cmd, t_envp **env, int a, t_exp *exp)
{
	if (do_quote_exp(&exp, cmd->files[a], *env, 1) == -1)
		return (-1);
	free(cmd->files[a]);
	if (!exp)
		cmd->files[a] = ft_strdup("");
	else
		cmd->files[a] = exp_to_str(exp);
	clear_exp(&exp);
	exp = NULL;
	if (!cmd->files[a])
		return (-1);
	return (0);
}

int	ft_expand_files(t_data *data, t_envp **env, int i)
{
	t_exp	*exp;
	int		a;
	int		is_amb;

	a = -1;
	exp = NULL;
	if (data->commands[i].files == NULL)
		return (0);
	while (data->commands[i].files[++a] != NULL)
	{
		is_amb = is_amb_cmd(ft_strdup(data->commands[i].files[a]), *env);
		if (is_amb == -1)
			return (-1);
		else if (is_amb == 1)
		{
			data->commands[i].is_ambiguous[a] = 1;
			continue ;
		}
		if (ft_not_amb(&data->commands[i], env, a, exp) == -1)
			return (-1);
	}
	return (0);
}
