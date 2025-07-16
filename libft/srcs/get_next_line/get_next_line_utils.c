/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:09:53 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 20:36:27 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str, int c)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len])
	{
		if (c == str[len])
			return (len + 1);
		len++;
	}
	return (len);
}

void	*ft_memmove_gnl(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (((char *)src) == 0 && ((char *)dest) == 0)
		return (dest);
	if (dest < src)
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
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
	dest[n] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, const char *s2, size_t *n)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc((ft_strlen_gnl(s1, '\0') + ft_strlen_gnl(s2, '\n') + 1));
	if (result == 0)
		return (free(s1), NULL);
	ft_bzero(result, (ft_strlen_gnl(s1, '\0') + ft_strlen_gnl(s2, '\n') + 1));
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j] && s2[j] != '\n')
		result[i + j] = s2[j];
	if (s2[j] == '\n')
		result[i + j] = '\n';
	if (result [i + j] == '\n')
		*n = j + 1;
	else
		*n = j;
	return (free(s1), result);
}

char	*ft_strdup_gnl(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((ft_strlen_gnl((char *)src, '\0') + 1));
	if (dest == 0)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
