/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:12:01 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:12:03 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

int	ft_buffer_flush(t_buffer *buffer, int fd)
{
	const int	l = buffer->length[fd];

	buffer->length[fd] = 0;
	return (write(fd, buffer->string[fd], l));
}

int	ft_buffer_cat(t_buffer *buffer, int fd, const char *s)
{
	int *const	length = buffer->length + fd;
	char		*string;
	int			ret_val;
	char		c;

	if (!s)
		return (0);
	string = buffer->string[fd];
	ret_val = 0;
	c = *s;
	while (c)
	{
		if (*length >= DPRINTF_BUFFERSIZE)
			ft_buffer_flush(buffer, fd);
		string[(*length)++] = c;
		if (c == '\n')
			ft_buffer_flush(buffer, fd);
		ret_val += 1;
		c = *(++s);
	}
	return (ret_val);
}

int	ft_buffer_cat_perc(t_buffer *buffer, int fd, const char *s)
{
	int *const	length = buffer->length + fd;
	char		*string;
	int			ret_val;
	char		c;

	if (!s)
		return (0);
	string = buffer->string[fd];
	ret_val = 0;
	c = *s;
	while (c && c != '%')
	{
		if (*length >= DPRINTF_BUFFERSIZE)
			ft_buffer_flush(buffer, fd);
		string[(*length)++] = c;
		if (c == '\n')
			ft_buffer_flush(buffer, fd);
		ret_val += 1;
		c = *(++s);
	}
	return (ret_val);
}
