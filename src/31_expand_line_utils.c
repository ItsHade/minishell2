/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:00:18 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 19:00:21 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	isset(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_printable(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int	is_redir(char *s, int i)
{
	i--;
	if (is_printable(s[i]) && !isset("<>", s[i]))
	{
		while (i > 0 && s[i] && is_printable(s[i]) && !isset("<>", s[i]))
			i--;
	}
	if (s[i] && isset(" 	", s[i]))
	{
		while (i > 0 && s[i] && isset(" 	", s[i]))
			i--;
	}
	if (s[i] && (s[i] == '>' || s[i] == '<'))
		return (i);
	return (0);
}

int	further_check_amb_str(char *s, int i)
{
	int	sp;
	int	nsp;

	sp = 0;
	nsp = 0;
	while (s[i])
	{
		if (s[i] && isset(" 	", s[i]))
		{
			while (s[i] && isset(" 	", s[i]))
				i++;
			sp++;
		}
		else if (s[i] && !isset(" 	", s[i]))
		{
			while (s[i] && !isset(" 	", s[i]))
				i++;
			nsp++;
		}
		if (sp == 1 && nsp == 2)
			return (1);
	}
	return (0);
}

int	check_amb_str(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (1);
	while (s[i] && isset(" 	", s[i]))
			i++;
	if (i && !s[i])
		return (1);
	return (further_check_amb_str(s, i));
}
