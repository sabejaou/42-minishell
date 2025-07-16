/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:56:32 by anfichet          #+#    #+#             */
/*   Updated: 2023/12/02 20:03:13 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *str, char c);
static void		ft_free(char **arr);
static char		**fill_array(char const *s, char c, char **arr);

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**arr;

	arr = 0;
	if (s == NULL)
		return (NULL);
	words = count_words((char *)s, c);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = fill_array((char *)s, c, arr);
	return (arr);
}

static size_t	count_words(char *str, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (str == NULL)
		return (count);
	while (str[i])
	{
		if (str[i] != c && ((str[i + 1] == c) || str[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}

static char	**fill_array(char const *s, char c, char **arr)
{
	size_t	j;
	size_t	start;
	size_t	end;

	start = 0;
	j = 0;
	while (s[start] && j < count_words((char *)s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		arr[j] = ft_substr((char *)s, start, end - start);
		if (!arr[j])
		{
			ft_free(arr);
			return (NULL);
		}
		start = end;
		j++;
	}
	return (arr);
}
