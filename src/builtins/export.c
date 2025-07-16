/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:53 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:34:29 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*namecpy(char *envar)
{
	int		i;
	char	*name;

	i = 0;
	while (envar[i] && envar[i] != '=')
		i++;
	name = ft_calloc(i + 2, sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, envar, i + 2);
	name[i + 1] = '\0';
	name[i] = '=';
	return (name);
}

char	*varequal(char *envar)
{
	char	*varequal;

	varequal = ft_calloc(sizeof(char), ft_strlen(envar) + 3);
	if (!varequal)
		return (NULL);
	ft_strlcpy(varequal, envar, ft_strlen(envar) + 3);
	ft_strlcat(varequal, "\'\'", ft_strlen(envar) + 3);
	return (varequal);
}

int	errvarname(char *argname)
{
	int	i;

	i = 1;
	while (argname[i] && argname[i] != '=')
	{
		if (!ft_isalnum(argname[i]) && argname[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_export(t_envp *envp, char *envar)
{
	t_exprt	e;

	e.argname = namecpy(envar);
	if ((!ft_isalpha(e.argname[0]) && e.argname[0] != '_')
		|| errvarname(e.argname) || !ft_strchr(envar, '='))
	{
		free(envar);
		ft_dprintf(2, "%s %s\n", e.argname, ERR_MSG_EXPORT_NAME);
		free(e.argname);
		return (1);
	}
	e.written = 0;
	e.i = size_env(envp->env_shell) + 2;
	e.newenv = ft_calloc(e.i, sizeof(char *));
	e.size = ft_strlen(e.argname);
	e.i = 0;
	while (e.newenv && envp->env_shell[e.i])
		builtin_export2(&e, envp, envar);
	if (e.argname && ft_strchr(envar, '=') && !e.written)
		e.newenv[e.i] = envar;
	free(envp->env_shell);
	free(e.argname);
	envp->env_shell = e.newenv;
	return (0);
}
