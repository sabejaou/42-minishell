/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:20 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:47:38 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_dollar_arg(char *arg, char **env)
{
	size_t	i;
	size_t	size;
	char	*arg_name;

	size = 0;
	i = 0;
	if (arg[i] == '$')
		arg++;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] == '\"')
		arg[i] = '\0';
	arg_name = ft_strndup(arg, i);
	size = ft_strlen(arg_name);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(arg_name, env[i], size - 1)
			&& (env[i][size] == '=')
				&& env[i][size - 1] == arg_name[size - 1])
			return (free(arg_name), ft_strlen(env[i]) - (size - 1));
	}
	return (free(arg_name), ft_strlen(arg) - size);
}

t_err	expand_spquote(char **content)
{
	char	*tmp;
	char	*new;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	tmp = *content;
	size = ft_strlen(*content);
	new = ft_calloc(size + 1, sizeof(char));
	while (new && tmp[i] && size)
	{
		if (tmp[i] && tmp[i] != '\'')
			new[j++] = tmp[i++];
		else
			i++;
	}
	if (new)
		new[j] = '\0';
	free(*content);
	*content = new;
	return (NO_ERROR);
}

t_err	expand_elems(t_elem **elems, char **env, int extsts)
{
	t_elem	*tmp;
	t_quote	*tmpq;

	tmp = *elems;
	while (tmp)
	{
		tmpq = tmp->quote;
		while (tmpq)
		{
			if (tmpq->stx_type == DBQUOTE)
				expand_dbquote(&(tmpq->quote), env, extsts);
			else if (tmpq->stx_type == SPQUOTE)
				expand_spquote(&(tmpq->quote));
			tmpq = tmpq->next;
		}
		tmp = tmp->next;
	}
	return (NO_ERROR);
}

void	expander(t_pipesep **seps, char **env, int extsts)
{
	t_pipesep	*tmp;

	tmp = *seps;
	while (tmp)
	{
		if (ft_error(expand_elems(&(tmp->elems), env, extsts)))
			return ;
		tmp = tmp->next;
	}
}
