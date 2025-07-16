/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:03 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:04 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_builtin(t_pipesep *seps)
{
	if ((ft_strncmp("pwd", seps->cmd[0], 4)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("cd", seps->cmd[0], 3)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("unset", seps->cmd[0], 6)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("export", seps->cmd[0], 7)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("echo", seps->cmd[0], 5)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("exit", seps->cmd[0], 5)) == 0)
		seps->builtin = true;
	else if ((ft_strncmp("env", seps->cmd[0], 4)) == 0)
		seps->builtin = true;
}

int	isbuiltin_cd(t_pipesep *seps)
{
	if ((!seps->cmd[1] || (seps->cmd[1] && !seps->cmd[2]))
		&& (ft_strncmp("cd", seps->cmd[0], 3)) == 0)
		return (1);
	return (0);
}

int	isbuiltin_cderr(t_pipesep *seps)
{
	if (seps->cmd[1] && seps->cmd[2] && ft_strncmp("cd", seps->cmd[0], 3) == 0)
		return (1);
	return (0);
}

int	builtin_function(t_pipesep *seps, t_envp *envp, t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if ((ft_strncmp("pwd", seps->cmd[0], 4)) == 0)
		i = builtin_pwd(envp);
	else if (isbuiltin_cd(seps))
		i = builtin_cd(envp, seps->cmd[1]);
	else if (isbuiltin_cderr(seps))
		i = ft_error(ERR_BUILTIN_CD);
	else if (seps->cmd[1] && (ft_strncmp("unset", seps->cmd[0], 6)) == 0)
		while (seps->cmd[j])
			i = builtin_unset(&envp, ft_strdup(seps->cmd[j++]));
	else if (seps->cmd[1] && (ft_strncmp("export", seps->cmd[0], 7)) == 0)
		while (seps->cmd[j])
			i = builtin_export(envp, ft_strdup(seps->cmd[j++]));
	else if ((ft_strncmp("echo", seps->cmd[0], 5)) == 0)
		i = builtin_echo(seps, seps->elems, seps->cmd);
	else if ((ft_strncmp("exit", seps->cmd[0], 5)) == 0)
		i = builtin_exit(seps, envp, exec);
	else if ((ft_strncmp("env", seps->cmd[0], 4)) == 0)
		i = builtin_env(envp);
	return (i);
}
