/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:44:37 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:44:46 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	do_exports(t_command *cmd, t_envp **ep, int i)
{
	char	**ags;
	int		ret;

	ret = 0;
	g_return = 0;
	if (cmd->cmd_arg[1] == NULL)
		return (print_export(*ep), 0);
	while (cmd->cmd_arg[++i] != NULL)
	{
		ags = NULL;
		ags = split_env(cmd->cmd_arg[i]);
		if (ags)
		{
			g_return = do_export(ags[0], ags[1], ep, cmd->cmd_arg[i]);
			free_content(ags);
			if (g_return == -1)
				return (g_return);
		}
		else
			ret = g_return;
	}
	if (g_return != 0)
		ret = g_return;
	return (ret);
}

int	do_export(char *name, char *value, t_envp **ep, char *cmd)
{
	t_envp	*t;

	t = *ep;
	if (!(ft_strcmp(name, "$?")) || ft_isdigit(name[0]) || inv_env_name(name))
		return (export_error(name, value, cmd));
	if (t)
	{
		while (t)
		{
			if (!(ft_strcmp(t->content[0], name)))
			{
				if ((t->content[1] && !(ft_strcmp(t->content[1], value)))
					|| !value)
					return (0);
				ft_free(t->content[1]);
				t->content[1] = ft_strdup(value);
				return (0);
			}
			t = t->next;
		}
	}
	return (build_new_envp(name, value, ep));
}

int	export_error(char *name, char *value, char *cmd)
{
	if (!(ft_strcmp(name, "$?")))
	{
		if (value)
			printf("Minishell: export: `0=%s': not a valid identifier\n", value);
		else
			printf("Minishell: export: `0': not a valid identifier\n");
	}
	else if (ft_isdigit(name[0]) || inv_env_name(name))
		printf("Minishell: export: `%s': not a valid identifier\n", cmd);
	return (1);
}

int	build_new_envp(char *name, char *value, t_envp **ep)
{
	char	**content;

	content = NULL;
	content = malloc(sizeof(char *) * 3);
	if (!(content))
	{
		perror("malloc failed in add_content");
		return (ft_fail_alloc(), -1);
	}
	content[0] = ft_strdup(name);
	content[1] = ft_strdup(value);
	content[2] = NULL;
	return (add_new_envp(ep, content));
}

char	**add_content(char *name, char *value)
{
	char	**content;

	content = NULL;
	content = malloc(sizeof(char *) * 3);
	if (!(content))
	{
		perror("malloc failed in add_content");
		g_return = -1;
		return (NULL);
	}
	content[0] = name;
	content[1] = value;
	content[2] = NULL;
	return (content);
}
