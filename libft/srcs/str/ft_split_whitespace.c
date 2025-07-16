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

static size_t	count_words(char *str);
static void		ft_free(char **arr);
static char		**fill_array(char const *s, char **arr);
static int		is_whitespace(char c);

char	**ft_split_whitespace(char const *s)
{
	size_t	words;
	char	**arr;

	arr = 0;
	if (s == NULL)
		return (NULL);
	words = count_words((char *)s);
	arr = ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = fill_array((char *)s, arr);
	return (arr);
}

static size_t	count_words(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (str == NULL)
		return (count);
	while (str[i])
	{
		if (!is_whitespace(str[i]) && (is_whitespace(str[i + 1]) \
			|| str[i + 1] == 0))
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

static char	**fill_array(char const *s, char **arr)
{
	size_t	j;
	size_t	start;
	size_t	end;

	start = 0;
	j = 0;
	while (s[start] && j < count_words((char *)s))
	{
		while (s[start] && is_whitespace(s[start]))
			start++;
		end = start;
		while (s[end] && (!is_whitespace(s[end])))
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

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\0' || c == '\t' || c == '\n' \
			|| c == '\v' || c == '\r' || c == '\f');
}
