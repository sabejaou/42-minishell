/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:14:32 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:14:33 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_elem	*ft_lstelem_new(char *content, t_tkn token, t_stx type, t_quote *quote)
{
	t_elem		*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->elem = content;
	new->id = token;
	new->quote = quote;
	new->stx_type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_elem	*ft_lstelemlast(t_elem *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstelemadd_back(t_elem **alst, t_elem *new)
{
	t_elem	*last;

	if (!new)
		return ;
	if (*alst)
	{
		last = ft_lstelemlast(*alst);
		last->next = new;
		new->prev = last;
	}
	else
		*alst = new;
}

size_t	count_elems(t_elem *elems)
{
	size_t	i;
	t_elem	*tmp;

	i = 0;
	tmp = elems;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + 1);
}
