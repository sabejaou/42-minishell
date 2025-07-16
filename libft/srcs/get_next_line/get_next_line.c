/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:09:31 by anfichet          #+#    #+#             */
/*   Updated: 2023/12/19 13:56:23 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1] = {0};
	char		*next_line;
	size_t		n;

	n = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_bzero(stash, BUFFER_SIZE + 1), NULL);
	if (ft_strchr(stash, '\n'))
		return (get_empty_line(stash, &n));
	next_line = ft_strdup_gnl(stash);
	if (next_line == 0)
		return (NULL);
	if (reading_line(fd, stash, &next_line, &n) == -1)
		return (NULL);
	ft_memmove(stash, &stash[n], ft_strlen_gnl(&stash[n], '\0') + 1);
	return (next_line);
}

char	*get_empty_line(char *stash, size_t *n)
{
	char	*next_line;
	char	*temp;

	temp = ft_strdup_gnl("");
	if (!temp)
		return (NULL);
	next_line = ft_strjoin_gnl(temp, stash, n);
	ft_memmove(stash, (stash + *n), ft_strlen_gnl((stash + *n), '\0') + 1);
	return (next_line);
}

int	reading_line(int fd, char *stash, char **next_line, size_t *n)
{
	ssize_t		size_read;

	size_read = 1;
	while (size_read > 0 && !ft_strchr(stash, '\n'))
	{
		size_read = read(fd, stash, BUFFER_SIZE);
		if (size_read == -1)
		{
			ft_bzero(stash, 1);
			free(*next_line);
			return (-1);
		}
		stash[size_read] = '\0';
		*next_line = ft_strjoin_gnl(*next_line, stash, n);
		if (*next_line == 0)
			return (-1);
	}
	if (*next_line[0] == '\0')
	{
		free(*next_line);
		return (-1);
	}
	return (0);
}
