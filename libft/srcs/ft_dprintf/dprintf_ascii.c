/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_ascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:11:35 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:11:36 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

int32_t	ft_char(t_buffer *buffer, int fd, char c)
{
	if (buffer->length[fd] >= DPRINTF_BUFFERSIZE)
		ft_buffer_flush(buffer, fd);
	buffer->string[fd][(buffer->length[fd])++] = c;
	if (c == '\n')
		ft_buffer_flush(buffer, fd);
	return (1);
}

int	ft_string(t_buffer *buffer, int fd, char *str)
{
	if (!str)
		return (ft_buffer_cat(buffer, fd, "(null)"));
	return (ft_buffer_cat(buffer, fd, str));
}

int	ft_pointer(char *out, t_buffer *buffer, int fd, uint64_t p)
{
	if (!p)
		return (ft_buffer_cat(buffer, fd, "(nil)"));
	ft_atoui64(out, (uint64_t)p, "0123456789abcdef", 16);
	return (ft_buffer_cat(buffer, fd, "0x"));
}
