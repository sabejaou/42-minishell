/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:40 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:13:41 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenise_quotes(t_tknarg *t, char *line, int *start)
{
	if (line[t->i] == '\"')
	{
		*start = (t)->i;
		while (line[++(t->i)] && line[(t)->i] != '\"')
			;
		ft_lstquoteadd_back(&(t->quote), ft_lstquote_new(
				ft_strndup(line + *start + 1, (t->i) - *start - 1), (t)->stx));
	}
	else if (line[t->i] == '\'')
	{
		(t)->stx = SPQUOTE;
		*start = t->i;
		while (line[++(t->i)] && line[(t->i)] != '\'')
			;
		ft_lstquoteadd_back(&(t->quote), ft_lstquote_new(
				ft_strndup(line + *start + 1, (t->i) - *start - 1), (t)->stx));
	}
}

void	tokenise_nquotes(t_tknarg *t, char *line, int *start)
{
	*start = (t)->i;
	while (line[++(t->i)] && line[(t)->i] != '\'' && line[(t)->i] != '\"'
		&& !ft_iswhitespace(line[(t)->i]) && line[(t)->i] != '<'
		&& line[(t->i)] != '>')
		;
	ft_lstquoteadd_back(&(t->quote), ft_lstquote_new(
			ft_strndup(line + *start, (t)->i - *start), (t)->stx));
	if (line[(t)->i] == '\'' || line[(t)->i] == '\"')
		(t->i)--;
}

int	tokeniseargvalid(char *line, int *i)
{
	if (line[++(*i)] && line[(*i)] != '\'' && line[(*i)] != '\"'
		&& !ft_iswhitespace(line[(*i)]) && line[(*i)] != '<'
		&& line[(*i)] != '>')
		return (1);
	return (0);
}

int	tokenise_file(t_elem **elems, int start, char *line)
{
	t_tknarg	t;

	t.i = 0;
	t.token = -1;
	t.quote = NULL;
	if (line[t.i] == '<' || line[t.i] == '>')
		tokenise_redir(&t, line);
	(t.i)++;
	while (ft_iswhitespace(line[t.i]))
		(t.i)++;
	while (line[t.i] && !ft_iswhitespace(line[t.i]) && !isredir(line, t))
	{
		t.stx = DBQUOTE;
		if (line[t.i] == '\"' || line[t.i] == '\'')
			tokenise_quotes(&t, line, &start);
		else if (!ft_iswhitespace(line[t.i]))
			tokenise_nquotes(&t, line, &start);
		if (line[t.i] && !ft_iswhitespace(line[t.i]) && !isredir(line, t))
			(t.i)++;
	}
	t.temp_dup = NULL;
	ft_lstelemadd_back(elems, ft_lstelem_new(
			t.temp_dup, t.token, t.stx, t.quote));
	return (t.i);
}

int	tokenise_arg(t_elem **elems, int start, char *line)
{
	t_tknarg	t;

	t.i = 0;
	t.quote = NULL;
	t.token = CMD;
	while (line[t.i] && !ft_iswhitespace(line[t.i])
		&& line[t.i] != '<' && line[t.i] != '>')
	{
		t.stx = DBQUOTE;
		if (line[t.i] == '\"' || line[t.i] == '\'')
			tokenise_quotes(&t, line, &start);
		else if (!ft_iswhitespace(line[t.i]))
			tokenise_nquotes(&t, line, &start);
		if (line[t.i] && !ft_iswhitespace(line[t.i])
			&& line[t.i] != '<' && line[t.i] != '>')
			(t.i)++;
	}
	t.temp_dup = NULL;
	ft_lstelemadd_back(elems, ft_lstelem_new(t.temp_dup,
			t.token, t.stx, t.quote));
	return (t.i);
}
