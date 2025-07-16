/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:25 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:50:59 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_exit_status(int extsts)
{
	size_t	size;
	char	*nbr;

	nbr = ft_itoa(extsts);
	size = ft_strlen(nbr);
	if (nbr)
		free(nbr);
	return (size + 1);
}

int	cancpychar(t_dbquote *d)
{
	if ((d)->tmp[(d)->i] && ((d)->tmp[(d)->i] != '$'
			|| ((d)->tmp[(d)->i] == '$' && (!(d)->tmp[(d)->i + 1]
					|| (!ft_isalpha((d)->tmp[(d)->i + 1])
						&& (d)->tmp[(d)->i + 1] != '?'
						&& (d)->tmp[(d)->i + 1] != '_')))))
		return (1);
	return (0);
}

int	cansizechar(char *elem, size_t i)
{
	if (elem[i] && (elem[i] != '$' || (elem[i] == '$' && (!elem[i + 1]
					|| (!ft_isalpha(elem[i + 1]) && elem[i + 1] != '?'
						&& elem[i + 1] != '_')))))
		return (1);
	return (0);
}

void	new_size_dbquote2(char *elem, size_t *i, size_t *new_size, char **env)
{
	if (!elem[*i + 1])
		(*i)++;
	else if (ft_isdigit(elem[*i + 1]))
		*i += 1;
	else if (elem[*i + 1] != '?')
	{
		*new_size += size_dollar_arg(elem + *i + 1, env);
	}
}

size_t	new_size_dbquote(char *elem, char **env, int extsts)
{
	size_t	new_size;
	size_t	i;

	i = 0;
	new_size = 0;
	while (elem[i])
	{
		if (cansizechar(elem, i))
			new_size++;
		else if (elem[i] && elem[i] == '$' && elem[i + 1]
			&& (ft_isalpha(elem[i + 1])
				|| elem[i + 1] == '?' || elem[i + 1] == '_'))
		{
			if (!elem[i + 1] || ft_isdigit(elem[i + 1]) || elem[i + 1] != '?')
				return (new_size_dbquote2(elem, &i, &new_size, env), new_size);
			else
			{
				new_size += size_exit_status(extsts);
				i += 2;
			}
		}
		if (elem[i])
			i++;
	}
	return (new_size);
}
