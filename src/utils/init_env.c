/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:44 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:45 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_elem_env(char **env);
static int		dup_env(char **env_array, char **env);

char	**init_envp(char **env)
{
	char	**env_array;
	size_t	size;

	size = count_elem_env(env);
	env_array = ft_calloc(size + 1, sizeof(char *));
	if (env_array == NULL)
		return (NULL);
	if (dup_env(env_array, env) == -1)
	{
		free_dbtab(env_array);
		return (NULL);
	}
	return (env_array);
}

static	int	dup_env(char **env_array, char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		if (env_array == NULL)
			return (-1);
		i++;
	}
	env_array[i] = NULL;
	return (NO_ERROR);
}

static size_t	count_elem_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}
