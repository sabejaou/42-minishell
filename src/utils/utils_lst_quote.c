/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:14:34 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:37 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote	*ft_lstquote_new(char *content, t_stx type)
{
	t_quote		*new;

	new = (t_quote *)ft_calloc(1, sizeof(t_quote));
	if (!new)
		return (NULL);
	new->quote = content;
	new->stx_type = type;
	new->next = NULL;
	return (new);
}

t_quote	*ft_lstquotelast(t_quote *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstquoteadd_back(t_quote **alst, t_quote *new)
{
	t_quote	*last;

	if (!new)
		return ;
	if (*alst)
	{
		last = ft_lstquotelast(*alst);
		last->next = new;
	}
	else
		*alst = new;
}
