/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:11:27 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/31 18:52:31 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

void	quote_error_loop(char *s, int *dq, int *sq, int *i)
{
	if (s[*i] && s[*i] == '\'')
	{
		(*sq)++;
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
		if (s[*i] && s[*i] == '\'')
			*sq = 0;
	}
	else if (s[*i] && s[*i] == '\"')
	{
		(*dq)++;
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
		if (s[*i] && s[*i] == '\"')
			*dq = 0;
	}
	if (s[*i])
		(*i)++;
}

int	quote_error(char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		quote_error_loop(s, &dq, &sq, &i);
	}
	if (sq || dq)
		return (ft_putstr_fd("unquoted issues >\n", 2), ft_free(s), 1);
	return (0);
}

int	check_syntax_error(t_token **tl, t_token *cur)
{
	if (cur)
	{
		g_return = 2;
		if (cur->label == PIPE && cur->index == 0)
			printf("minishell: syntax error near unexpected token `%s'\n",
				(char *)cur->value);
		else if (cur->next)
			printf("minishell: syntax error near unexpected token `%s'\n",
				(char *)cur->next->value);
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		return (ft_lstclear(tl), -1);
	}
	return (0);
}

int	syntax_error(t_token **tl)
{
	t_token	*cur;

	cur = *tl;
	if (!cur)
		return (EMPTY);
	while (cur)
	{
		if ((cur->label == I_RDR || cur->label == O_RDR || cur->label == HEREDOC
				|| cur->label == OAPPEND) && (!cur->next))
			break ;
		if ((cur->label == I_RDR || cur->label == O_RDR || cur->label == HEREDOC
				|| cur->label == OAPPEND) && (cur->next->label != WORD))
			break ;
		if (cur->label == PIPE && ((cur->prev && cur->prev->label != WORD)
				|| cur->next == NULL || cur->next->label == PIPE))
			break ;
		if (cur->label == PIPE && cur->index == 0)
			break ;
		if (cur->label == SYNTAX)
			break ;
		cur = cur->next;
	}
	return (check_syntax_error(tl, cur));
}
