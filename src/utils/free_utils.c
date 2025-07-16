/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:42 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:49 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lst_quote(t_quote *quote)
{
	t_quote	*tmp;

	tmp = quote->next;
	while (quote)
	{
		if (quote->quote)
			free(quote->quote);
		if (quote)
			free(quote);
		quote = tmp;
		if (quote)
			tmp = quote->next;
	}
	quote = NULL;
}

void	free_dbtab(char **db_array)
{
	size_t	i;

	i = 0;
	if (!db_array)
		return ;
	while (db_array[i])
	{
		free(db_array[i]);
		db_array[i] = NULL;
		i++;
	}
	free(db_array);
	db_array = NULL;
}

void	free_lst_seps(t_pipesep **seps)
{
	t_pipesep		*tmp;
	t_pipesep		*head;

	head = (*seps);
	while (seps && head)
	{
		tmp = head->next;
		if (head->cmd)
			free_dbtab(head->cmd);
		if (head->line)
			free(head->line);
		if (head->elems)
			free_lst_elem(head->elems);
		if (head)
			free(head);
		head = tmp;
	}
	seps = NULL;
}

void	free_lst_elem(t_elem *elem)
{
	t_elem	*tmp;

	while (elem)
	{
		tmp = elem->next;
		if (elem->elem)
			free(elem->elem);
		if (elem->quote)
			free_lst_quote(elem->quote);
		if (elem)
			free(elem);
		elem = tmp;
	}
	elem = NULL;
}
