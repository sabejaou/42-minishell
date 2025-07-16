/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:12 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:37 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	save_dup_std_builtin(t_exec *exec);
static int	restore_dup_std_builtin(t_exec *exec);

t_err	execution_builtin(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	if (save_dup_std_builtin(exec) == -1)
	{
		envp->exit_status = 1;
		return (envp->exit_status);
	}
	open_files(seps, envp, exec);
	if (dup_builtin(seps, envp) == ERR_DUP)
		exit(envp->exit_status);
	envp->exit_status = builtin_function(seps, envp, exec);
	if (restore_dup_std_builtin(exec) == -1)
	{
		envp->exit_status = 1;
		return (envp->exit_status);
	}
	close_builtin(exec);
	return (NO_ERROR);
}

static int	save_dup_std_builtin(t_exec *exec)
{
	exec->tmp_stdin = dup(STDIN_FILENO);
	if (exec->tmp_stdin == -1)
	{
		ft_dprintf(2, "minishell: dup error: %s\n", strerror(errno));
		return (-1);
	}
	exec->tmp_stdout = dup(STDOUT_FILENO);
	if (exec->tmp_stdout == -1)
	{
		ft_dprintf(2, "minishell: dup error: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

static int	restore_dup_std_builtin(t_exec *exec)
{
	if (dup2(exec->tmp_stdin, STDIN_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup error: %s\n", strerror(errno));
		return (-1);
	}
	if (dup2(exec->tmp_stdout, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup error: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

void	close_builtin(t_exec *exec)
{
	close_and_check_error(exec->tmp_stdin, "dup stdin");
	close_and_check_error(exec->tmp_stdout, "dup stdout");
}
