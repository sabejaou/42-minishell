/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:26 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:33 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_err	open_error(t_pipesep *seps, int file, char *name, t_envp *envp)
{
	(void)envp;
	if (file == -1)
	{
		ft_dprintf(2, "minishell: open error %s : %s\n", name, strerror(errno));
		close_pipe(seps, NULL);
		free_lst_seps(&seps->head);
		exit(1);
	}
	return (NO_ERROR);
}

t_err	open_error_p(t_pipesep *seps, int file, char *name, t_envp *envp)
{
	(void)seps;
	(void)envp;
	if (file == -1)
	{
		ft_dprintf(2, "minishell: open error open error %s : %s\n", \
		name, strerror(errno));
		free_lst_seps(&seps->head);
		return (1);
	}
	return (NO_ERROR);
}

void	close_and_check_error(int file, char *name)
{
	if (file != -1)
	{
		if (close(file) != 0)
			ft_dprintf(2, "minishell: close error: %s : %s\n", \
			name, strerror(errno));
	}
	if (file != -1 && close(file) == 0)
		file = -1;
}
