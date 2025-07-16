/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_inner.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:12:19 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:12:30 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DPRINTF_INNER_H
# define DPRINTF_INNER_H
# define DPRINTF_BUFFERSIZE 4096
# define FD_NUMBER 127
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

struct s_buffer
{
	char		string[FD_NUMBER][DPRINTF_BUFFERSIZE];
	int32_t		length[FD_NUMBER];
	int			fd;
};

typedef struct s_buffer	t_buffer;

/* buffer.c */
int32_t		ft_buffer_flush(t_buffer *buffer, int32_t fd);
int32_t		ft_buffer_cat(t_buffer *buffer, int32_t fd, const char *s);
int32_t		ft_buffer_cat_perc(t_buffer *buffer, int32_t fd, const char *s);
/* specifier.c */
int32_t		ft_specifier(const char *format, va_list args, t_buffer *buffer);
/* ascii.c */
int32_t		ft_char(t_buffer *buffer, int fd, char c);
int32_t		ft_string(t_buffer *buffer, int fd, char *str);
int32_t		ft_pointer(char *out, t_buffer *buffer, int fd, uint64_t p);
/* atoi32.c */
void		ft_atoi32(char *out, int32_t n, const char *abase, uint8_t base);
void		ft_atoui32(char *out, uint32_t n, const char *abase, uint8_t base);
/* atoi64.c */
void		ft_atoi64(char *out, int64_t n, const char *abase, uint8_t base);
void		ft_atoui64(char *out, uint64_t n, const char *abase, uint8_t base);
/* utils.c */
uint8_t		ft_logb(int64_t n, uint8_t base);
uint8_t		ft_logbu(uint64_t n, uint8_t base);
void		*ft_dbzero(void *s, unsigned long n);

#endif
