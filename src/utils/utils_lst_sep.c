/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:14:37 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:14:38 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipesep	*ft_lstsep_new(char *content)
{
	t_pipesep		*new;

	new = (t_pipesep *)ft_calloc(sizeof(t_pipesep), sizeof(t_pipesep));
	if (!new)
		return (NULL);
	new->builtin = 0;
	new->line = content;
	new->elems = NULL;
	new->cmd = NULL;
	new->infile = -1 ;
	new->outfile = -1;
	new->fd_pipe[0] = -1;
	new->fd_pipe[1] = -1;
	new->len_seps = 0;
	new->name_heredoc = NULL;
	new->head = NULL;
	new->next = NULL;
	return (new);
}

t_pipesep	*ft_lstseplast(t_pipesep *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstaddsep_back(t_pipesep **alst, t_pipesep *new)
{
	t_pipesep	*last;

	if (!new)
		return ;
	if (*alst)
	{
		last = ft_lstseplast(*alst);
		last->next = new;
	}
	else
		*alst = new;
}

size_t	count_seps(t_pipesep *seps)
{
	size_t	i;

	i = 0;
	while (seps)
	{
		seps = seps->next;
		i++;
	}
	return (i);
}

void	affect_len(t_pipesep *seps)
{
	size_t		len;
	t_pipesep	*head;

	head = seps;
	len = count_seps(seps);
	while (seps)
	{
		seps->len_seps = len;
		seps->head = head;
		seps = seps->next;
	}
}
