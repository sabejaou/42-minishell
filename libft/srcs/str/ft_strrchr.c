/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:21:06 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/24 16:52:18 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen((char *)str);
	while (i > 0 && str[i] != (char)c)
		i--;
	if (str[i] == (char)c)
		return (&((char *)str)[i]);
	return (NULL);
}
