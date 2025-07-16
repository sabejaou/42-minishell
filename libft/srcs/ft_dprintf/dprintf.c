/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:12:14 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:12:16 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dprintf_inner.h"

static void	_init_buf(int must_init, \
		char string[FD_NUMBER][DPRINTF_BUFFERSIZE], \
		int length[FD_NUMBER]);

int	ft_dprintf(int fd, const char *format, ...)
{
	static t_buffer	buffer = {.fd = -1};
	va_list			vargs;
	int32_t			i;
	int32_t			tmp;
	int32_t			ret_val;

	if (!format || fd < 0 || write(1, 0, 0) == -1)
		return (-1);
	_init_buf(buffer.fd == -1, buffer.string, buffer.length);
	va_start(vargs, format);
	buffer.fd = fd;
	ret_val = 0;
	i = 0;
	while (format[i])
	{
		tmp = ft_buffer_cat_perc(&buffer, fd, format + i);
		ret_val = ret_val * (tmp >= 0) + tmp * (ret_val > -1);
		i += tmp;
		if (format[i] != '%')
			continue ;
		tmp = ft_specifier(format + i + 1, vargs, &buffer);
		ret_val = ret_val * (tmp >= 0) + tmp * (ret_val > -1);
		i += 2;
	}
	return (va_end(vargs), ret_val);
}

static void	_init_buf(int must_init, \
		char string[FD_NUMBER][DPRINTF_BUFFERSIZE], \
		int length[FD_NUMBER])
{
	if (!must_init)
		return ;
	ft_bzero((char *)string, FD_NUMBER * DPRINTF_BUFFERSIZE);
	ft_bzero((char *)length, FD_NUMBER * sizeof(*length));
}
