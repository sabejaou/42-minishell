/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:50 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:15:39 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_env_l(char **env, const char *name)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(name) - 1;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], size - 1)
			&& (env[i][size] == '=' || !env[size]))
			return (i);
		i++;
	}
	return (-1);
}

char	*remove_last_file(char *l)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (l[i])
	{
		while (l[i] && l[i] != '/')
			i++;
		if (l[i])
			j = i;
		i++;
	}
	new = malloc(j - 3);
	ft_strlcpy(new, l + 4, j - 3);
	printf("new=%s\n", new);
	return (new);
}

char	*new_pwd(char *pwd)
{
	char	*new;

	if (!pwd)
		return (NULL);
	new = ft_calloc(ft_strlen(pwd) + 5, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, "PWD=", ft_strlen(pwd) + 5);
	ft_strlcat(new, pwd, ft_strlen(pwd) + 5);
	return (new);
}

char	*new_oldpwd(char *pwd)
{
	char	*new;

	if (!pwd)
		return (NULL);
	new = ft_calloc(ft_strlen(pwd) + 4, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, "OLD", ft_strlen(pwd) + 4);
	ft_strlcat(new, pwd, ft_strlen(pwd) + 4);
	return (new);
}
