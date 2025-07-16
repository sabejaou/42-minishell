/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:15:52 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:15:53 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_envp *envp)
{
	int	i;

	i = 0;
	while (envp->env_shell && envp->env_shell[i])
	{
		if (ft_printf("%s\n", envp->env_shell[i]) == -1)
			return (2);
		i++;
	}
	return (0);
}
