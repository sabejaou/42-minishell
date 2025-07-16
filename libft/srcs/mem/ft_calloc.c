/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:00:54 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/25 13:50:37 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size > __SIZE_MAX__ / nmemb)
		return (NULL);
	tab = malloc(size * nmemb);
	if (tab == 0)
		return (NULL);
	ft_bzero(tab, (nmemb * size));
	return (tab);
}
