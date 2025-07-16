/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catelems.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:27 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:13:28 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_checkelems(t_pipesep *seps)
{
	t_pipesep	*tmpseps;
	t_elem		*tmpelm;

	tmpseps = seps;
	if (!tmpseps->elems)
		return (1);
	while (tmpseps)
	{
		tmpelm = seps->elems;
		while (tmpelm)
		{
			if (!tmpelm->elem)
				return (1);
			tmpelm = tmpelm->next;
		}
		tmpseps = tmpseps->next;
	}
	return (0);
}

size_t	sizequotes(t_quote *quote)
{
	t_quote	*tmp;
	size_t	len;

	len = 0;
	tmp = quote;
	while (tmp)
	{
		len += ft_strlen(tmp->quote);
		tmp = tmp->next;
	}
	return (len);
}

void	catelems(t_elem **tmpe)
{
	t_quote		*tmpq;
	size_t		len;

	while ((*tmpe))
	{
		tmpq = (*tmpe)->quote;
		len = sizequotes(tmpq);
		free((*tmpe)->elem);
		(*tmpe)->elem = ft_calloc(len + 1, sizeof(char));
		while (tmpq)
		{
			ft_strlcat((*tmpe)->elem, tmpq->quote, len + 1);
			tmpq = tmpq->next;
		}
		(*tmpe) = (*tmpe)->next;
	}
}

void	elemscat(t_pipesep **seps)
{
	t_pipesep	*tmp;
	t_elem		*tmpe;

	tmp = *seps;
	while (tmp)
	{
		tmpe = tmp->elems;
		if (tmp && tmp->elems && (!tmp->elems->quote
				|| !tmp->elems->quote->quote || !*tmp->elems->quote->quote)
			&& !tmp->elems->quote->next)
		{
			tmp->elems->elem = NULL;
			ft_error(NO_ERROR);
		}
		else
		{
			catelems(&tmpe);
		}
		tmp = tmp->next;
	}
}
