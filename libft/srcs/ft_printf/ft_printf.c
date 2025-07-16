/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:42:53 by anfichet          #+#    #+#             */
/*   Updated: 2023/12/02 19:20:56 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	size_t	i;
	int		count;
	int		totalprint;

	totalprint = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	va_start(arg, str);
	while (str[i] != '\0')
	{
		count = 0;
		ft_print(&count, str, &i, arg);
		if (count == -1)
		{
			return (-1);
			va_end(arg);
		}
		else
			totalprint += count;
		i++;
	}
	va_end(arg);
	return (totalprint);
}

void	ft_print(int *addr_count, const char *str, size_t *addr_i, va_list arg)
{
	if (str[*addr_i] == '%' && is_specifier(str[*addr_i + 1]))
	{
		ft_print_format(str[*addr_i + 1], arg, addr_count);
		(*addr_i)++;
	}
	else
		ft_print_first_arg(str, addr_i, addr_count);
}

void	ft_print_format(const char specifier, va_list arg, int *addr_count)
{
	if (specifier == 'c')
		ft_putchar_pf(va_arg(arg, int), addr_count);
	else if (specifier == 's')
		ft_putstr_pf(va_arg(arg, char *), addr_count);
	else if (specifier == 'd' || specifier == 'i')
		ft_putnbr_base(va_arg(arg, int), BASE10, addr_count);
	else if (specifier == 'u')
		ft_unsigned_putnbr(va_arg(arg, unsigned int), BASE10, addr_count);
	else if (specifier == 'x')
		ft_unsigned_putnbr(va_arg(arg, unsigned int), BASE16_LOWER, addr_count);
	else if (specifier == 'X')
		ft_unsigned_putnbr(va_arg(arg, unsigned int), BASE16_UPPER, addr_count);
	else if (specifier == '%')
		ft_putchar_pf('%', addr_count);
	else if (specifier == 'p')
		ft_put_address(va_arg(arg, unsigned long int), addr_count);
}

void	ft_print_first_arg(const char *str, size_t *addr_i, int *addr_count)
{
	size_t	lenpercent;
	size_t	count;
	ssize_t	written;

	count = 0;
	lenpercent = ft_strlenpercent(&str[*addr_i]);
	if (str[*addr_i] == '%' && !is_specifier(str[*addr_i + 1]))
	{
		check_percent(str, addr_count, addr_i);
		(*addr_i)++;
	}
	while (count < lenpercent)
	{
		written = write(1, &str[*addr_i] + count, lenpercent - count);
		count += written;
		if (written == -1)
			*addr_count = -1;
	}
	*addr_count += count;
	*addr_i += lenpercent - 1;
}

void	check_percent(const char *str, int *addr_count, size_t *addr_i)
{
	int	count_percent;
	int	i;

	i = 0;
	count_percent = 0;
	while (str[i])
	{
		if (str[i] == '%')
			count_percent++;
		i++;
	}
	if (str[*addr_i] == '%' && str[*addr_i + 1] == '\0' && count_percent == 1)
	{
		*addr_count = -1;
		return ;
	}
	if (str[*addr_i] == '%')
		ft_putchar_pf('%', addr_count);
}
