/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:37 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:27:35 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printquotes(t_quote *quote)
{
	t_quote	*tmp;

	tmp = quote;
	while (tmp)
	{
		printf("quote:%s\nstx:%d\n", tmp->quote, tmp->stx_type);
		tmp = tmp->next;
	}
}

int	skipspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i += 1;
	return (i);
}

void	tokenise_redir(t_tknarg *t, char *line)
{
	if (line[t->i] == '<')
	{
		if (line[(t->i) + 1] == '<')
		{
			t->token = HEREDOC;
			(t->i)++;
		}
		else
			t->token = INFILE;
	}
	else if (line[t->i] == '>')
	{
		if (line[(t->i) + 1] == '>')
		{
			t->token = OUTFILE_APP;
			(t->i)++;
		}
		else if (line[t->i + 1])
			t->token = OUTFILE;
	}
}

t_elem	*tokenise_line(char *line)
{
	int		i;
	int		start;
	t_elem	*elems;

	i = 0;
	elems = NULL;
	start = 0;
	while (line && line[i])
	{
		i += skipspaces(line + i);
		start = i;
		if (line[i] && line[i] != '<' && line[i] != '>')
			i += tokenise_arg(&elems, start, line + i);
		else if (line[i])
			i += tokenise_file(&elems, start, line + i);
	}
	return (elems);
}

void	tokeniser(t_pipesep **seps)
{
	t_pipesep	*tmp;

	tmp = *seps;
	while (tmp)
	{
		tmp->elems = tokenise_line(tmp->line);
		tmp = tmp->next;
	}
}
