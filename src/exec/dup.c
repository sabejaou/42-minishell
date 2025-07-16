/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:09 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:10 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dup_child_in(t_pipesep *seps, t_exec *exec, t_envp *envp);
static int	dup_child_out(t_pipesep *seps, t_envp *envp);

t_err	dup_builtin(t_pipesep *seps, t_envp *envp)
{
	if (seps->infile != -1)
	{
		if (dup2(seps->infile, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error : %s\n", strerror(errno));
			free_lst_seps(&seps->head);
			free_dbtab(envp->env_shell);
			envp->exit_status = 1;
			return (ERR_DUP);
		}
		close_and_check_error(seps->infile, "dup file");
	}
	if (seps->outfile != -1)
	{
		if (dup2(seps->outfile, STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error : %s\n", strerror(errno));
			free_lst_seps(&seps->head);
			free_dbtab(envp->env_shell);
			envp->exit_status = 1;
			return (ERR_DUP);
		}
		close_and_check_error(seps->outfile, "dup file");
	}
	return (NO_ERROR);
}

t_err	dup_child(t_pipesep *seps, t_exec *exec, t_envp *envp)
{
	if (dup_child_in(seps, exec, envp) == -1)
	{
		envp->exit_status = 1;
		free_lst_seps(&seps->head);
		free_dbtab(envp->env_shell);
		return (ERR_DUP);
	}
	if (dup_child_out(seps, envp) == -1)
	{
		envp->exit_status = 1;
		free_lst_seps(&seps->head);
		free_dbtab(envp->env_shell);
		return (ERR_DUP);
	}
	return (NO_ERROR);
}

static int	dup_child_in(t_pipesep *seps, t_exec *exec, t_envp *envp)
{
	(void)envp;
	if (seps->infile != -1)
	{
		if (dup2(seps->infile, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error in: %s\n", strerror(errno));
			return (-1);
		}
		close_and_check_error(exec->tmp_fd_pipe_in, "dup file");
		close_and_check_error(seps->infile, "dup file");
	}
	else if (seps->infile == -1 && exec->time != 1)
	{
		if (dup2(exec->tmp_fd_pipe_in, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error in2: %s\n", strerror(errno));
			return (-1);
		}
		close_and_check_error(exec->tmp_fd_pipe_in, "dup file");
	}
	return (0);
}

static int	dup_child_out(t_pipesep *seps, t_envp *envp)
{
	(void)envp;
	if (seps->outfile != -1)
	{
		if (dup2(seps->outfile, STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error out: %s\n", strerror(errno));
			return (-1);
		}
		close_and_check_error(seps->outfile, "dup file");
	}
	else if (seps->outfile == -1 && seps->next != NULL)
	{
		if (dup2(seps->fd_pipe[1], STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup error out2: %s\n", strerror(errno));
			return (-1);
		}
	}
	return (0);
}
