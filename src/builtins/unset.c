/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:14:01 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:33:45 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_checkvar(char **env, char *envar, size_t size)
{
	int		i;
	bool	exist;

	i = 0;
	exist = 0;
	while (env[i])
	{
		if (!ft_strncmp(envar, env[i], size) && (env[i][size] == '='))
			exist = 1;
		i++;
	}
	if (exist)
		return (0);
	else
		return (1);
}

void	builtin_unset2(t_envp **envp, int i, char **newenv, char *envar)
{
	free((*envp)->env_shell);
	free(envar);
	newenv[i - 1] = NULL;
	(*envp)->env_shell = newenv;
}

int	builtin_unset(t_envp **envp, char *envar)
{
	int		i;
	int		j;
	size_t	size;
	char	**newenv;

	size = ft_strlen(envar);
	if (ft_checkvar((*envp)->env_shell, envar, size))
		return (0);
	i = size_env((*envp)->env_shell);
	newenv = ft_calloc(i, sizeof(char *));
	if (!newenv)
		return (1);
	i = 0;
	j = 0;
	while ((*envp)->env_shell[i])
	{
		if (!ft_strncmp(envar, (*envp)->env_shell[i], size)
			&& ((*envp)->env_shell[i][size] == '='))
			free((*envp)->env_shell[i++]);
		else
			newenv[j++] = (*envp)->env_shell[i++];
	}
	builtin_unset2(envp, i, newenv, envar);
	return (0);
}
