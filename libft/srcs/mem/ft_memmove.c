/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:46:49 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/14 18:40:25 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (((char *)src) == 0 && ((char *)dest) == 0)
		return (dest);
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
	}
	if (dest > src)
	{
		while (n != 0)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
		return (dest);
	}
	return (dest);
}
