/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:47:07 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 18:47:08 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_sep(char c)
{
	int			i;
	const char	sep[4] = " 	";

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_meta(char c)
{
	int			i;
	const char	meta[5] = "|<>";

	i = 0;
	while (meta[i])
	{
		if (c == meta[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_quote(char c)
{
	int			i;
	const char	quote[5] = "'\"";

	i = 0;
	while (quote[i])
	{
		if (c == quote[i])
			return (1);
		i++;
	}
	return (0);
}
