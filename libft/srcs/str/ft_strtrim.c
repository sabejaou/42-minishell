/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:10:26 by anfichet          #+#    #+#             */
/*   Updated: 2023/12/02 20:02:46 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_charset(const char *str, int c);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (ft_charset(set, (int)s1[i]))
	{
		start++;
		i++;
	}
	i = end;
	while (ft_charset(set, (int)s1[i]))
	{
		end--;
		i--;
	}
	return (ft_substr(s1, start, end - start + 1));
}

static char	*ft_charset(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (&((char *)str)[i]);
	return (NULL);
}
