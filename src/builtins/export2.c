/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 19:13:58 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export2(t_exprt *e, t_envp *envp, char *envar)
{
	if (ft_strncmp(e->argname, envp->env_shell[e->i], e->size))
	{
		e->newenv[e->i] = envp->env_shell[e->i];
	}
	else if (ft_strchr(envar, '=') && !e->written)
	{
		free(envp->env_shell[e->i]);
		e->newenv[e->i] = envar;
		e->written = 1;
	}
	else if (!e->written)
	{
		e->newenv[e->i] = varequal(e->argname);
		e->written = 1;
		free(envar);
	}
	(e->i)++;
}
