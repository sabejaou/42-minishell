/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:24:52 by anfichet          #+#    #+#             */
/*   Updated: 2023/12/02 20:03:00 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen((char *)s2);
	result = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (result == 0)
		return (NULL);
	ft_strlcpy(result, (char *)s1, len1 + len2 + 1);
	ft_strlcat(result, (char *)s2, len1 + len2 + 1);
	return (result);
}
