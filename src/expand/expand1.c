/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:22 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:52:27 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	copy_dollar_arg2(t_cpyarg *a, char **env, size_t *cat, char **new)
{
	if (!ft_strncmp((a)->arg_name, env[(a)->i], (a)->size - 1)
		&& env[(a)->i][(a)->size] == '='
			&& env[(a)->i][(a)->size - 1] == (a)->arg_name[(a)->size - 1])
	{
		free((a)->arg_name);
		(a)->tmpe = ft_strdup(env[a->i] + (a)->size + 1);
		ft_strlcat(*new, (a)->tmpe, *cat);
		free((a)->tmpe);
		return ((a)->size + 1);
	}
	(a)->i += 1;
	return (0);
}

size_t	copy_dollar_arg(char **new, char *arg, char **env, size_t cat)
{
	t_cpyarg	a;

	(a).size = 0;
	(a).tmp = 0;
	if (arg[(a).tmp] == '$')
		arg++;
	while (arg[(a).tmp] && (ft_isalnum(arg[(a).tmp]) || arg[(a).tmp] == '_'))
		((a).tmp)++;
	if (arg[(a).tmp] == '\"')
		arg[(a).tmp] = '\0';
	(a).arg_name = ft_strndup(arg, (a).tmp);
	(a).size = ft_strlen((a).arg_name);
	(a).i = 0;
	while (env[(a).i])
	{
		if (copy_dollar_arg2(&a, env, &cat, new))
			return (a.size + 1);
	}
	free((a).arg_name);
	return ((a).size + 1);
}

size_t	copy_exit_status(char **new, size_t cat, int extsts)
{
	char	*nbr;

	nbr = ft_itoa(extsts);
	ft_strlcat(*new, nbr, cat);
	if (nbr)
		free(nbr);
	return (2);
}

void	expand_dbquote2(t_dbquote *d, char **env, int extsts)
{
	if ((d)->tmp[(d)->i] == '$' && ft_isdigit((d)->tmp[(d)->i + 1]))
		(d)->i += 2;
	else if (cancpychar(d))
		(d)->new[(d->j)++] = (d)->tmp[(d)->i++];
	else if ((d)->tmp[(d)->i] == '$' && (ft_isalpha((d)->tmp[(d)->i + 1])
			|| (d)->tmp[(d)->i + 1] == '?' || (d)->tmp[(d)->i + 1] == '_'))
	{
		if ((d)->tmp[(d)->i + 1] != '?')
		{
			(d)->i += copy_dollar_arg(&(d)->new, (d)->tmp + (d)->i + 1, env,
					(d)->size + 1);
			(d)->j = ft_strlen((d)->new);
			if (!(d)->i)
				while ((d)->tmp[(d)->i] && !ft_iswhitespace((d)->tmp[(d)->i]))
					(d->i)++;
		}
		else
		{
			(d)->i += copy_exit_status(&(d)->new, (d)->size + 1, extsts);
			(d)->j = ft_strlen((d)->new);
		}
	}
	else if ((d)->tmp[(d)->i])
		(d->i)++;
}

t_err	expand_dbquote(char **content, char **env, int extsts)
{
	t_dbquote	db;

	ft_bzero(&db, sizeof(db));
	(db).tmp = *content;
	if (*(db).tmp == '\"')
		(db).tmp++;
	(db).size = new_size_dbquote(db.tmp, env, extsts);
	if ((db).size)
		(db).new = ft_calloc((db).size + 1, sizeof(char));
	else
		(db).new = NULL;
	while (db.tmp[db.i] && db.size)
		expand_dbquote2(&db, env, extsts);
	free(*content);
	if ((db).new && !((db).new[0]))
	{
		free((db).new);
		(db).new = NULL;
	}
	*content = (db).new;
	if (ft_strlen((db).new) && (db).new[ft_strlen((db).new) - 1] == '\"')
		(db).new[ft_strlen((db).new) - 1] = '\0';
	return (NO_ERROR);
}
