/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:03:27 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/22 17:03:29 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_cmd_info(t_token **next_cmd, int *nb_arg, int *nb_io)
{
	t_token	*current;

	current = *next_cmd;
	*nb_arg = 0;
	*nb_io = 0;
	while (current && current->label != PIPE)
	{
		if (current->label == ARG || current->label == CMD)
			(*nb_arg)++;
		else if (current->label == I_RDR || current->label == O_RDR
			|| current->label == OAPPEND || current->label == HEREDOC)
			(*nb_io)++;
		current = current->next;
	}
	return (0);
}

int	ft_get_args2(t_command *command, t_token *current, int a)
{
	while (a < command->nb_arg && current != NULL)
	{
		if (current->label == CMD || current->label == ARG)
		{
			command->cmd_arg[a] = ft_strdup(current->value);
			if (!command->cmd_arg[a])
				return (perror("ft_calloc"), ft_fail_alloc(), -1);
			a++;
		}
		current = current->next;
	}
	return (0);
}

int	ft_get_args(t_command *command, t_token **token_list)
{
	t_token	*current;
	int		a;

	a = 0;
	command->cmd_arg = NULL;
	current = *token_list;
	if (command->nb_arg < 1)
	{
		command->cmd_arg = ft_calloc(sizeof(char *), 1);
		if (!command->cmd_arg)
			return (perror("ft_calloc"), ft_fail_alloc(), -1);
		command->cmd_arg[0] = NULL;
		return (0);
	}
	command->cmd_arg = ft_calloc(sizeof(char *), command->nb_arg + 1);
	if (!command->cmd_arg)
		return (perror("ft_calloc"), ft_fail_alloc(), -1);
	if (ft_get_args2(command, current, a) == -1)
		return (-1);
	return (0);
}

int	ft_get_redir2(t_command *command, t_token *current, int a)
{
	while (a < command->nb_io && current != NULL)
	{
		if (current->label == I_RDR || current->label == O_RDR
			|| current->label == OAPPEND || current->label == HEREDOC)
		{
			command->redir[a] = current->label;
			command->files[a] = ft_strdup(current->next->value);
			a++;
		}
		current = current->next;
	}
	return (0);
}

int	ft_get_redir(t_command *command, t_token **next_cmd)
{
	int		a;
	t_token	*current;

	current = *next_cmd;
	a = 0;
	command->files = NULL;
	command->redir = NULL;
	if (command->nb_io < 1)
		return (0);
	command->files = ft_calloc(sizeof(char *), (command->nb_io + 1));
	if (!command->files)
		return (perror("ft_calloc"), ft_fail_alloc(), -1);
	command->redir = ft_calloc(sizeof(t_label), (command->nb_io));
	if (!command->redir)
		return (perror("ft_c"), ft_fail_alloc(), -1);
	if (ft_get_redir2(command, current, a) == -1)
		return (-1);
	return (0);
}
