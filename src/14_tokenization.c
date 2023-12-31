/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:30:22 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/31 13:04:06 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_quote_word_len(char *line, int *i, char *quote, int *in_quotes)
{
	int	len;

	len = 0;
	if (line[*i] && is_quote(line[*i]) && *in_quotes == 0)
	{
		*in_quotes = 1;
		*quote = line[*i];
		(*i)++;
		len++;
	}
	if (line[*i] && *in_quotes == 1)
	{
		if (line[*i] == *quote)
			*in_quotes = 0;
		(*i)++;
		len++;
	}
	if (line[*i] && !is_sep(line[*i]) && !is_meta(line[*i])
		&& !is_quote(line[*i]) && *in_quotes == 0)
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	ft_get_amb(t_command *command)
{
	command->is_ambiguous = ft_calloc(sizeof(int), command->nb_io);
	if (!command->is_ambiguous)
		return (perror("ft_calloc in ft_get_amb"), -1);
	return (0);
}
