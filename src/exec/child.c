/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:06 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:07 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_child(t_pipesep *seps, t_envp *envp);

int	child(t_pipesep *seps, t_elem *elem, t_exec *exec, t_envp *envp)
{
	(void)elem;
	signal(SIGQUIT, SIG_DFL);
	open_files(seps, envp, exec);
	if (dup_child(seps, exec, envp) == ERR_DUP)
	{
		free_child(seps, envp);
		exit(envp->exit_status);
	}
	close_pipe(seps, NULL);
	if (seps->builtin == 1)
	{
		envp->exit_status = builtin_function(seps, envp, exec);
		free_child(seps, envp);
	}
	else
	{
		search_path(seps, envp);
		if (seps->cmd && seps->cmd[0] == NULL)
			free_child(seps, envp);
		else if (execve(seps->cmd[0], seps->cmd, envp->env_shell) == -1)
			free_child(seps, envp);
	}
	exit(envp->exit_status);
}

void	close_pipe(t_pipesep *seps, t_exec *exec)
{
	if (seps->fd_pipe[0] != -1)
	{
		if (close(seps->fd_pipe[0]) != 0)
			ft_dprintf(2, "minishell: close fd error: %s\n", strerror(errno));
	}
	if (seps->fd_pipe[1] != -1)
	{
		if (close(seps->fd_pipe[1]) != 0)
			ft_dprintf(2, "minishell: close fd error: %s\n", strerror(errno));
	}
	if (exec != NULL && exec->tmp_fd_pipe_in != -1)
		if (close(exec->tmp_fd_pipe_in) != 0)
			ft_dprintf(2, "Close error exec 1 %d : %s\n", \
					exec->tmp_fd_pipe_in, strerror(errno));
}

static void	free_child(t_pipesep *seps, t_envp *envp)
{
	free_lst_seps(&seps->head);
	free_dbtab(envp->env_shell);
}
