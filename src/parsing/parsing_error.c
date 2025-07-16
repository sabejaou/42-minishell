/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:30 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:13:31 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
		if (str[i] == '|')
			return (1);
		while (str[i] && str[i] != '|')
			i++;
		if (str[i] == '|')
		{
			i++;
			if (!str[i])
				return (1);
		}
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i])
		return (0);
	return (1);
}

t_err	ft_checklinequote(char *line, int *i)
{
	if (line[(*i)] == '\"')
	{
		while (line[++(*i)] && line[(*i)] != '\"')
			;
		if (!line[(*i)])
			return (ERR_DBQUOTE);
		(*i)++;
	}
	else if (line[(*i)] == '\'')
	{
		while (line[++(*i)] && line[(*i)] != '\'')
			;
		if (!line[(*i)])
			return (ERR_SPQUOTE);
		(*i)++;
	}
	return (NO_ERROR);
}

t_err	ft_checklineredir(char *line, int *i)
{
	if (line[(*i)] == '<')
	{
		(*i)++;
		if (line[(*i)] == '>')
			return (ERR_SYNTAX_FILE);
		if (line[(*i)] == '<')
			(*i)++;
		while (ft_iswhitespace(line[(*i)]))
			(*i)++;
		if (line[(*i)] == '>' || line[(*i)] == '<' || !line[(*i)])
			return (ERR_SYNTAX_FILE);
	}
	else if (line[(*i)] == '>')
	{
		(*i)++;
		if (line[(*i)] == '<')
			return (ERR_SYNTAX_FILE);
		if (line[(*i)] == '>')
			(*i)++;
		while (ft_iswhitespace(line[(*i)]))
			(*i)++;
		if (line[(*i)] == '>' || line[(*i)] == '<' || !line[(*i)])
			return (ERR_SYNTAX_FILE);
	}
	return (NO_ERROR);
}
/* Gestion des erreurs de quotes non fermees */

t_err	ft_checkline(char *line)
{
	int		i;
	t_err	e;

	i = 0;
	while (line[i])
	{
		if (check_pipe(line))
			return (ERR_SPACE);
		if (line[i] == '\"' || line[i] == '\'')
		{
			e = ft_checklinequote(line, &i);
			if (e)
				return (e);
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			e = ft_checklineredir(line, &i);
			if (e)
				return (e);
		}
		else
			i++;
	}
	return (0);
}
