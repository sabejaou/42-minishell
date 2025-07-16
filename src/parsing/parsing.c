/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:43 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:13:44 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isredir(char *line, t_tknarg t)
{
	if (line[t.i] == '<' || line[t.i] == '>')
		return (1);
	return (0);
}

void	ft_pipesep2(char *line, int *i)
{
	if (line[(*i)] == '\"')
	{
		while (line[++(*i)] && line[(*i)] != '\"')
			;
		(*i)++;
	}
	else if (line[(*i)] == '\'')
	{
		while (line[++(*i)] && line[(*i)] != '\'')
			;
		(*i)++;
	}
	else
		(*i)++;
}

// separation de la string des elements entre les pipes dans un maillon
t_pipesep	*ft_pipesep(char *line)
{
	int			i;
	int			start;
	t_pipesep	*seps;
	char		*temp_dup;

	i = 0;
	seps = NULL;
	while (line[i])
	{
		start = i;
		while (line[i] && line[i] != '|')
		{
			ft_pipesep2(line, &i);
		}
		temp_dup = ft_strndup(line + start, i - start);
		if (!temp_dup)
			return (NULL);
		ft_lstaddsep_back(&seps, ft_lstsep_new(temp_dup));
		if (line[i])
			i++;
	}
	return (seps);
}

int	cmdinit(t_pipesep **tmp, t_pipesep **seps)
{
	*tmp = *seps;
	(*tmp)->builtin = 0;
	if ((*tmp)->elems && !(*tmp)->elems->elem)
		return (1);
	return (0);
}

void	createcmd(t_pipesep **seps)
{
	t_elem		*elem;
	size_t		i;
	t_pipesep	*tmp;

	if (cmdinit(&tmp, seps))
		return ;
	while (tmp)
	{
		i = 0;
		elem = tmp->elems;
		tmp->cmd = ft_calloc(count_elems(elem), sizeof(char *));
		if (!tmp->cmd)
			return ;
		while (elem)
		{
			if (elem->id == CMD)
			{
				tmp->cmd[i++] = ft_strdup(elem->elem);
				if_builtin(tmp);
			}
			elem = elem->next;
		}
		tmp->cmd[i] = NULL;
		tmp = tmp->next;
	}
}
