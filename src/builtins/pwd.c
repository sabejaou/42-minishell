/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:01 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:02 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_get_env(t_envp *envp, char *var);

int	builtin_pwd(t_envp *envp)
{
	char	*pwd;

	(void)envp;
	pwd = ft_get_env(envp, "PWD=");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (2);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}

static char	*ft_get_env(t_envp *envp, char *var)
{
	int	i;

	i = 0;
	while (envp->env_shell && envp->env_shell[i])
	{
		if (ft_strncmp(var, envp->env_shell[i], ft_strlen(var)) == 0)
			return (envp->env_shell[i] + ft_strlen(var));
		i++;
	}
	return (NULL);
}
