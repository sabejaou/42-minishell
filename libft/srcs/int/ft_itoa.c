/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:08:11 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/25 18:53:45 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long int n)
{
	size_t	digit;

	digit = 0;
	if (n == 0)
		digit++;
	if (n < 0)
	{
		digit++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	char		*nbstr;
	size_t		digit;
	long int	ln;

	ln = n;
	digit = ft_len(ln);
	nbstr = ft_calloc(digit + 1, sizeof(char));
	if (!nbstr)
		return (NULL);
	if (ln < 0)
	{
		ln = -ln;
		nbstr[0] = '-';
	}
	while (ln > 9)
	{
		nbstr[digit - 1] = ln % 10 + 48;
		ln = ln / 10;
		digit--;
	}
	nbstr[digit - 1] = ln % 10 + 48;
	return (nbstr);
}

/*int	main(void)
 {
 	int	nb = 0;
 	printf("%s\n", ft_itoa(nb));
 	return (0);
 }*/