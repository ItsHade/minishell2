/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:16:20 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 12:16:22 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_nb_of_cmd(t_token **token_list)
{
	int		count;
	t_token	*current;

	count = 0;
	current = *token_list;
	if (current != NULL)
		count = 1;
	while (current)
	{
		if (current->label == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	ft_go_to_next_cmd(t_token **next_cmd)
{
	while (*next_cmd && (*next_cmd)->label != PIPE)
		*next_cmd = (*next_cmd)->next;
	if (*next_cmd && (*next_cmd)->next && (*next_cmd)->label == PIPE)
		*next_cmd = (*next_cmd)->next;
}

int	ft_fill_cmd_table(t_token **token_list, t_data *data)
{
	int		i;
	t_token	*next_cmd;

	i = 0;
	next_cmd = *token_list;
	data->nb_cmd = ft_nb_of_cmd(token_list);
	data->commands = ft_calloc(sizeof(t_command), (data->nb_cmd + 1));
	if (!data->commands)
		return (perror("ft_calloc"), ft_fail_alloc(), -1);
	while (i < data->nb_cmd)
	{
		ft_get_cmd_info(&next_cmd, &data->commands[i].nb_arg,
			&data->commands[i].nb_io);
		if (ft_get_redir(&data->commands[i], &next_cmd) == -1)
			return (-1);
		if (ft_get_args(&data->commands[i], &next_cmd) == -1)
			return (-1);
		if (ft_get_amb(&data->commands[i]) == -1)
			return (-1);
		if (next_cmd != NULL)
			ft_go_to_next_cmd(&next_cmd);
		i++;
	}
	return (0);
}

void	ft_check_tokens(t_token *cur, int *cmd)
{
	if (cur->label == HEREDOC && cur->next)
		cur->next->label = LIMITER;
	if ((cur->label == I_RDR || cur->label == O_RDR || cur->label == OAPPEND)
		&& cur->next)
		cur->next->label = IO_FILE;
	if (cur->label == PIPE && cur->next && cur->next->label == WORD)
		cur->next->label = CMD;
	if (cur->label == WORD && cur->index == 0)
	{
		cur->label = CMD;
		*cmd = 1;
	}
	if (cur->label == CMD && cur->next && cur->next->label == WORD)
		cur->next->label = ARG;
	if (cur->label == ARG && cur->next && cur->next->label == WORD)
		cur->next->label = ARG;
	if (cur->label == IO_FILE && cur->next && cur->next->label == WORD)
		cur->next->label = ARG;
	if ((cur->label == WORD || cur->label == ARG) && cmd == 0)
	{
		cur->label = CMD;
		*cmd = 1;
	}
	if (cur->label == PIPE)
		*cmd = 0;
}

int	ft_parsing(t_token **token_list, t_data *data)
{
	t_token	*cur;
	int		cmd;

	cur = *token_list;
	cmd = 0;
	while (cur)
	{
		if (cur->index == 0 && cur->label == PIPE)
			return (-1);
		ft_check_tokens(cur, &cmd);
		cur = cur->next;
	}
	if (ft_fill_cmd_table(token_list, data) == -1)
		return (-1);
	if (data->nb_cmd < 1)
		return (ft_freecmdtable(data), ft_lstclear(token_list), -1);
	return (0);
}
