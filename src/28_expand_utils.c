/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:12:36 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 19:15:26 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

int	do_not_exp_dq(t_exp **exp, char *s, int i)
{
	int	start;

	start = i;
	if (s[i] == '$')
		i++;
	if (s[i] && s[i] == '$')
		i++;
	while (s[i] && s[i] != '\"' && s[i] != '$')
		i++;
	if (add_new_exp(exp, ft_substr(s, start, i - start)) == -1)
		return (-1);
	return (i);
}

int	do_dq(t_exp **exp, char *s, int i, t_envp *ep)
{
	i++;
	if (s[i] == '\"')
		return (i + 1);
	while (s[i] && s[i] != '\"')
	{
		if (s[i] == '$' && s[i + 1] && (is_env(s[i + 1])
				|| s[i + 1] == '?'))
			i = do_dollar(exp, s, i, ep);
		else
			i = do_not_exp_dq(exp, s, i);
		if (i == -1)
			return (-1);
	}
	return (i + 1);
}

char	*exp_to_str(t_exp *exp)
{
	char	*s;

	s = NULL;
	while (exp)
	{
		s = ft_strjoinf(s, exp->s);
		if (!s)
			return (NULL);
		exp = exp->next;
	}
	return (s);
}
