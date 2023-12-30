/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:21:04 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 11:21:14 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_words(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_next_word_len(line, &i) > 0)
			count++;
	}
	return (count);
}

int	ft_stacked_word(char *line, int *i)
{
	int	stacked;
	int	len;

	stacked = 0;
	len = 0;
	while (line[*i] && is_meta(line[*i]) && stacked < 2)
	{
		if (line[*i] == '|')
			stacked = 3;
		(*i)++;
		len++;
		stacked++;
	}
	return (len);
}

int	ft_next_word_len(char *line, int *i)
{
	int		in_quotes;
	int		len;
	char	quote;

	in_quotes = 0;
	len = 0;
	while (line[*i] && is_sep(line[*i]))
		(*i)++;
	while (line[*i])
	{
		if (line[*i] && is_meta(line[*i]) && in_quotes == 0 && len == 0)
		{
			len += ft_stacked_word(line, i);
			break ;
		}
		else if (line[*i] && is_meta(line[*i]) && in_quotes == 0 && len != 0)
			break ;
		len += ft_quote_word_len(line, i, &quote, &in_quotes);
		if (line[*i] && is_sep(line[*i]) && in_quotes == 0)
			break ;
	}
	return (len);
}

char	*ft_get_next_word(char *line, int *i)
{
	char	*word;
	int		a;
	int		len;

	a = 0;
	len = ft_next_word_len(line, i);
	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (perror("ft_calloc"), NULL);
	*i -= len;
	while (line[*i] && a < len)
	{
		word[a] = line[*i];
		a++;
		(*i)++;
	}
	word[a] = '\0';
	return (word);
}

int	ft_get_token_list(t_token **tl, char *l)
{
	int		nb_of_tokens;
	int		a;
	t_token	*new;
	char	*word;
	int		i;

	a = 0;
	i = 0;
	nb_of_tokens = ft_count_words(l);
	while (a < nb_of_tokens)
	{
		word = ft_get_next_word(l, &i);
		if (!word)
			return (-1);
		new = ft_lstnew((void *)word);
		if (!new)
			return (-1);
		ft_lstadd_back(tl, new);
		a++;
	}
	return (0);
}
