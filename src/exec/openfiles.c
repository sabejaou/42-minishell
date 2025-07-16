/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:16 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:18 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_outfile(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec);
static int	open_infile(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec);
static int	open_infile_hd(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec);

t_err	open_files(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	t_elem	*tmp_elem;

	(void)envp;
	tmp_elem = seps->elems;
	while (tmp_elem != NULL)
	{
		open_infile(seps, tmp_elem, envp, exec);
		open_outfile(seps, tmp_elem, envp, exec);
		tmp_elem = tmp_elem->next;
	}
	return (NO_ERROR);
}

static int	open_infile(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec)
{
	if (tmp_elem->id == INFILE)
	{
		if (seps->infile != -1)
			close_and_check_error(seps->infile, tmp_elem->prev->elem);
		seps->infile = open(tmp_elem->elem, INFILE);
		if (seps->infile == -1)
		{
			ft_dprintf(2, "minishell: open error %s: %s\n", tmp_elem->elem, \
						strerror(errno));
			if (seps->name_heredoc)
				unlink(seps->name_heredoc);
			close_pipe(seps, exec);
			free_lst_seps(&seps->head);
			free_dbtab(envp->env_shell);
			exit (1);
		}
	}
	if (tmp_elem->id == HEREDOC)
	{
		if (open_infile_hd(seps, tmp_elem, envp, exec) != 0)
			return (ERR_OPEN);
	}
	return (NO_ERROR);
}

static int	open_infile_hd(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec)
{
	if (seps->infile != -1)
	{
		if (close(seps->infile) != 0)
		{
			ft_dprintf(2, "minishell: close error: %s : %s\n", \
				tmp_elem->prev->elem, strerror(errno));
			unlink(tmp_elem->elem);
		}
	}
	seps->infile = open(tmp_elem->elem, O_RDONLY);
	open_error(seps, seps->infile, tmp_elem->elem, envp);
	if (exec->tmp_fd_pipe_in != -1)
		if (close(exec->tmp_fd_pipe_in) != 0)
			ft_dprintf(2, "Close error exec 1 %d : %s\n", \
			exec->tmp_fd_pipe_in, strerror(errno));
	unlink(tmp_elem->elem);
	return (NO_ERROR);
}

static int	open_outfile(t_pipesep *seps, t_elem *tmp_elem, \
t_envp *envp, t_exec *exec)
{
	(void)exec;
	if (tmp_elem->id == OUTFILE || tmp_elem->id == OUTFILE_APP)
	{
		if (seps->outfile != -1)
			close_and_check_error(seps->outfile, tmp_elem->prev->elem);
		if (tmp_elem->id == OUTFILE)
			seps->outfile = open(tmp_elem->elem, OUTFILE, 0644);
		else if (tmp_elem->id == OUTFILE_APP)
			seps->outfile = open(tmp_elem->elem, OUTFILE_APP, 0644);
		open_error(seps, seps->outfile, tmp_elem->elem, envp);
	}
	return (0);
}
