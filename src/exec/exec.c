/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:14 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:15 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_exit_status(t_pipesep *seps, t_envp *envp, \
t_exec *exec, int status);
static void	close_wait_child(t_pipesep *seps, t_envp *envp, \
t_exec *exec);
static int	pipe_and_fork(t_pipesep *seps, t_envp *envp, t_exec *exec);
static void	init_exec_and_redir(t_exec *exec, t_pipesep *seps, t_envp *envp);

int	execution(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	init_exec_and_redir(exec, seps, envp);
	if (seps->len_seps == 1 && seps->builtin == 1)
		execution_builtin(seps, envp, exec);
	else
	{
		while (seps && g_signal != SIGINT)
		{
			if (pipe_and_fork(seps, envp, exec) != 0)
				return (1);
			if (exec->pid == 0)
				child(seps, seps->elems, exec, envp);
			close_and_check_error(exec->tmp_fd_pipe_in, "tmp_fd_pipe_in");
			exec->tmp_fd_pipe_in = dup(seps->fd_pipe[0]);
			if (exec->tmp_fd_pipe_in == -1)
			{
				ft_dprintf(2, "minishell: dup error: %s\n", strerror(errno));
				exit (1);
			}
			close_pipe(seps, NULL);
			seps = seps->next;
		}
		if (g_signal != SIGINT)
			close_wait_child(seps, envp, exec);
	}
	return (envp->exit_status);
}

static void	init_exec_and_redir(t_exec *exec, t_pipesep *seps, t_envp *envp)
{
	exec->time = 0;
	exec->tmp_fd_pipe_in = -1;
	exec->tmp_stdin = -1;
	exec->tmp_stdout = -1;
	init_redir_hd(seps, envp);
}

static int	pipe_and_fork(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	(void)envp;
	if (pipe(seps->fd_pipe) == -1)
	{
		ft_dprintf(2, "minishell: pipe error : %s\n", strerror(errno));
		return (ERR_PIPE);
	}
	exec->pid = fork();
	exec->time++;
	if (exec->pid == -1)
	{
		ft_dprintf(2, "minishell: fork error : %s\n", strerror(errno));
		return (ERR_FORK);
	}
	return (0);
}

static void	close_wait_child(t_pipesep *seps, t_envp *envp, \
t_exec *exec)
{
	int	status;

	status = 0;
	if (exec->tmp_fd_pipe_in != -1)
		if (close(exec->tmp_fd_pipe_in) != 0)
			ft_dprintf(2, "minishell : close error %d : %s\n", \
			exec->tmp_fd_pipe_in, strerror(errno));
	waitpid(exec->pid, &status, 0);
	while (wait(0) != -1)
		;
	set_exit_status(seps, envp, exec, status);
}

static void	set_exit_status(t_pipesep *seps, t_envp *envp, \
t_exec *exec, int status)
{
	(void)exec;
	(void)seps;
	if (WIFEXITED(status))
	{
		envp->exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		envp->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
}
