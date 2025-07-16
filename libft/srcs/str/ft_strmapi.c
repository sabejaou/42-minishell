/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:58:08 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/25 19:10:49 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	newstr = ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	if (f)
	{
		while (s[i])
		{
			newstr[i] = f(i, s[i]);
			i++;
		}
	}
	return (newstr);
}
