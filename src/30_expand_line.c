/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_expand_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhuang <yzhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:46:25 by yzhuang           #+#    #+#             */
/*   Updated: 2023/12/30 20:56:31 by yzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_return;

char	*get_env_value(char *s, int dollar, t_envp *ep)
{
	int		i;
	char	*env_name;
	char	*env_value;

	env_name = NULL;
	env_value = NULL;
	i = dollar;
	i++;
	while (s[i] && is_env(s[i]))
		i++;
	env_name = ft_substr(s, dollar + 1, i - dollar - 1);
	if (!env_name)
		return (perror("ft_calloc"), ft_fail_alloc(), NULL);
	env_value = ft_getenv(env_name, ep);
	ft_free(env_name);
	env_name = NULL;
	return (env_value);
}

int	is_ambiguous(char *s, int dl, t_envp *ep)
{
	int		is_r;
	char	*t;
	int		i;
	int		ret;

	t = NULL;
	i = dl;
	is_r = is_redir(s, dl);
	if (!is_r && !isset("<>", s[0]))
		return (0);
	while (s[i] && !isset(" 	", s[i]))
		i++;
	t = ft_substr(s, is_r + 1, i - is_r - 1);
	if (!t)
		return (-1);
	dl = 0;
	while (t[dl] && t[dl] != '$')
		dl++;
	if (add_dollar_str(&t, dl, ep) == -1)
		return (-1);
	ret = check_amb_str(t);
	ft_free(t);
	return (ret);
}

int	add_dollar_str(char **line, int i, t_envp *ep)
{
	int		i_dollar;
	char	*env_value;
	char	*t1;
	char	*t2;

	i_dollar = i;
	env_value = get_env_value(*line, i_dollar, ep);
	if (!env_value && g_return == -1)
		return (-1);
	i++;
	while ((*line)[i] && is_env((*line)[i]))
		i++;
	if (env_value || (!env_value
			&& (!(*line)[i] || (isset(" 	|$", (*line)[i])))))
	{		
		t1 = ft_substr(*line, 0, i_dollar);
		t2 = ft_substr(*line, i, ft_strlen(*line) - i);
		ft_free(*line);
		*line = NULL;
		i = i_dollar + ft_strlen(env_value);
		*line = ft_strjoinf(t1, env_value);
		*line = ft_strjoinf(*line, t2);
		ft_free(t2);
	}
	return (i);
}

int	do_dollar_line(char **line, int i, t_envp *ep)
{
	int	is_amb;

	if ((*line)[i + 1] && (isset("$?", (*line)[i + 1])))
		i += 2;
	else if ((*line)[i + 1] && is_env((*line)[i + 1]))
	{
		is_amb = is_ambiguous((*line), i, ep);
		if (is_amb == -1)
			return (-1);
		else if (is_amb)
		{
			while ((*line)[i] && !isset(" 	", (*line)[i]))
				i++;
		}
		else
			i = add_dollar_str(line, i, ep);
		if (i == -1)
			return (-1);
	}
	else
		i++;
	return (i);
}
