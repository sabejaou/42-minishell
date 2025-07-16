/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_atoi64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:11:52 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:11:54 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dprintf_inner.h"

void	ft_atoi64(char *out, int64_t n, const char *abase, uint8_t base)
{
	const uint16_t	log = ft_logb(n, base);
	const uint8_t	negative = n < 0;
	int64_t			tmp;
	uint16_t		i;

	tmp = (n + (n == (int64_t)0x8000000000000000));
	tmp *= !negative - negative;
	i = log + negative;
	out[0] = '-';
	out[i] = abase[tmp % base];
	i += (n != 0);
	while (i > negative)
	{
		out[--i] = abase[tmp % base];
		tmp = tmp / base;
	}
	if ((uint64_t)n == 0x8000000000000000)
		out[10] += 1;
}

void	ft_atoui64(char *out, uint64_t n, const char *abase, uint8_t base)
{
	uint16_t	i;

	i = ft_logbu(n, base);
	out[i] = abase[n % base];
	i += (n != 0);
	while (i > 0)
	{
		out[--i] = abase[n % base];
		n /= base;
	}
}
