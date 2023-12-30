/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:05:49 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 19:15:02 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_dollar(t_exp **exp, char *s, int i, t_envp *ep)
{
	int		i_dollar;
	char	*env_name;

	i_dollar = i;
	i++;
	if (s[i] == '\"' || s[i] == '\'')
		return (i);
	if (s[i] && (s[i] == '$' || s[i] == '?'))
	{
		env_name = ft_substr(s, i, 1);
		if (add_exp_value(exp, env_name, ep) == -1)
			return (-1);
		i++;
	}
	else if (s[i] && ft_isdigit(s[i]))
			i++;
	else if (s[i] && is_env(s[i]))
	{
		while (s[i] && is_env(s[i]))
			i++;
		env_name = ft_substr(s, i_dollar + 1, i - i_dollar - 1);
		if (add_exp_value(exp, env_name, ep) == -1)
			return (-1);
	}
	return (i);
}

int	do_sq(t_exp **exp, char *s, int i)
{
	int	start;

	i++;
	start = i;
	while (s[i] && s[i] != '\'')
		i++;
	if (s[i] && s[i] == '\'' && i != start)
	{
		if (add_new_exp(exp, ft_substr(s, start, i - start)) == -1)
			return (-1);
	}	
	return (i + 1);
}

int	do_not_exp(t_exp **exp, char *s, int i)
{
	int	start;

	start = i;
	if (s[i] == '$')
		i++;
	if (s[i] && s[i] == '$')
		i++;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		i++;
	if (add_new_exp(exp, ft_substr(s, start, i - start)) == -1)
		return (-1);
	return (i);
}

int	do_tilde(t_exp **exp, char *s, t_envp *ep)
{
	char	*t;
	int		start;
	int		i;
	char	*substr;

	substr = NULL;
	t = NULL;
	i = 1;
	start = 0;
	if (s[0] == '~' && (!s[1] || s[1] == '/'))
		t = ft_getenv("HOME", ep);
	if (t)
		start = 1;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		i++;
	substr = ft_substr(s, start, i - start);
	if (!substr)
		return (-1);
	t = ft_strjoin(t, substr);
	ft_free(substr);
	if (!t)
		return (-1);
	if (add_new_exp(exp, t) == -1)
		return (-1);
	return (i);
}

int	do_quote_exp(t_exp **exp, char *s, t_envp *ep, int mode)
{
	int	i;

	i = 0;
	if (s[0] == '~' && mode)
	{
		i = do_tilde(exp, s, ep);
		if (i == -1)
			return (-1);
	}
	while (s[i])
	{
		if (s[i] == '\'')
			i = do_sq(exp, s, i);
		else if (s[i] == '\"')
			i = do_dq(exp, s, i, ep);
		else if (s[i] == '$' && s[i + 1] && (is_env(s[i + 1])
				|| s[i + 1] == '?' || s[i + 1] == '\"' || s[i + 1] == '\''))
			i = do_dollar(exp, s, i, ep);
		else
			i = do_not_exp(exp, s, i);
		if (i == -1)
			return (-1);
	}
	return (0);
}
