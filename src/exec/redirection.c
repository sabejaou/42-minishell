/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:23 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:24 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_err	affect_name_heredoc(t_pipesep *seps, t_envp *envp);
static t_err	create_heredoc(char *delimiter, t_pipesep *seps, t_envp *envp);
static void		complete_name(unsigned char *tmp);

int	init_redir_hd(t_pipesep *seps, t_envp *envp)
{
	t_pipesep	*tmp;

	tmp = seps;
	while (tmp)
	{
		if (open_heredoc(tmp, envp) == 130)
			return (envp->exit_status);
		tmp = tmp->next;
	}
	return (0);
}

int	open_heredoc(t_pipesep *seps, t_envp *envp)
{
	t_elem	*tmp;

	(void)envp;
	tmp = seps->elems;
	while (tmp != NULL && g_signal != SIGINT)
	{
		if (tmp->id == HEREDOC)
		{
			if (seps->infile != -1)
				close_and_check_error(seps->infile, tmp->elem);
			envp->exit_status = create_heredoc(tmp->elem, seps, envp);
			free(tmp->elem);
			tmp->elem = seps->name_heredoc;
			seps->infile = open(tmp->elem, O_RDONLY);
			open_error(seps, seps->infile, tmp->elem, envp);
		}
		tmp = tmp->next;
	}
	if (seps->infile != -1)
	{
		close_and_check_error(seps->infile, seps->name_heredoc);
		seps->infile = -1;
	}
	return (envp->exit_status);
}

static t_err	create_heredoc(char *delimiter, t_pipesep *seps, t_envp *envp)
{
	char			*line;
	int				file;

	affect_name_heredoc(seps, envp);
	file = open(seps->name_heredoc, O_RDWR | O_CREAT | O_EXCL, 0644);
	open_error(seps, file, seps->name_heredoc, envp);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_dprintf(2, "minishell: warning: here-document delimited by end-of-file \
			(wanted %s)\n", delimiter);
			break ;
		}
		if ((ft_strcmp(delimiter, line) == 0) || g_signal == SIGINT)
			break ;
		ft_dprintf(file, "%s\n", line);
		free(line);
	}
	if (g_signal == SIGINT)
		return (close_and_check_error(file, seps->name_heredoc), 128 + SIGINT);
	free(line);
	close_and_check_error(file, seps->name_heredoc);
	return (NO_ERROR);
}

static t_err	affect_name_heredoc(t_pipesep *seps, t_envp *envp)
{
	int				urandom;
	unsigned char	tmp[6];

	urandom = 0;
	ft_memset(tmp, 0, 6);
	urandom = open("/dev/urandom", O_RDONLY);
	open_error(seps, urandom, "/dev/urandom", envp);
	if (read(urandom, tmp, 5) != 5)
	{
		close_and_check_error(urandom, "/dev/urandom");
		return (ERR_READ);
	}
	close_and_check_error(urandom, "/dev/urandom");
	complete_name(tmp);
	seps->name_heredoc = ft_strjoin("/tmp/minishell_", (char *)tmp);
	if (seps->name_heredoc == NULL)
		return (-1);
	return (NO_ERROR);
}

static void	complete_name(unsigned char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] >= 'a' && tmp[i] <= 'z')
			i++;
		else
		{
			tmp[i] = tmp[i] % 26 + 'a';
			i++;
		}
	}
	tmp[i] = '\0';
}
