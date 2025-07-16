/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:48 by sabejaou          #+#    #+#             */
/*   Updated: 2024/06/24 20:16:18 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd2(char **arg, t_builtincd *c, t_envp *envp, size_t l)
{
	if (!(*arg) || !*(*arg))
	{
		if (c->home_l == -1)
		{
			if (c->oldpath)
				free(c->oldpath);
			return (ft_error(ERR_BUILTIN_CD_HOME), 1);
		}
		c->newpath = ft_strdup(envp->env_shell[c->home_l] + 5);
	}
	else if (c->oldpath && ((*arg)[0] != '/' || ((*arg)[0] != '/'
		&& (*arg)[0] == '.' && (*arg)[1] != '.')))
	{
		if ((*arg)[0] == '.' && (*arg)[1] == '/')
			(*arg) += 2;
		c->newpath = ft_calloc(l + ft_strlen((*arg)) + 2, sizeof(char));
		ft_strlcat(c->newpath, c->oldpath + 4, l + ft_strlen((*arg)) + 1);
		ft_strlcat(c->newpath, "/", l + ft_strlen((*arg)) + 1);
		ft_strlcat(c->newpath, (*arg), l + ft_strlen((*arg)) + 1);
	}
	else if (c->oldpath && (*arg)[0] == '.' && (*arg)[1] == '.')
		c->newpath = remove_last_file(c->oldpath);
	else
		c->newpath = ft_strdup((*arg));
	return (0);
}

int	builtin_cd3(t_builtincd *c, t_envp *envp)
{
	if (chdir(c->newpath) != 0)
	{
		if (c->newpath)
			free(c->newpath);
		if (c->oldpath)
			free(c->oldpath);
		perror("cd: chdir");
		return (1);
	}
	if (c->pwd_l >= 0)
	{
		free(envp->env_shell[c->pwd_l]);
		envp->env_shell[c->pwd_l] = new_pwd((getcwd(c->buf, PATH_MAX)));
	}
	if (c->pwd_l >= 0 && !envp->env_shell[c->pwd_l])
	{
		if (c->newpath)
			free(c->newpath);
		if (c->oldpath)
			free(c->oldpath);
		perror("cd: dont exist");
		return (1);
	}
	return (0);
}

int	builtin_cd(t_envp *envp, char *arg)
{
	t_builtincd	c;

	c.pwd_l = search_env_l(envp->env_shell, "PWD=");
	c.oldpwd_l = search_env_l(envp->env_shell, "OLDPWD=");
	c.home_l = search_env_l(envp->env_shell, "HOME=");
	c.oldpath = NULL;
	c.newpath = NULL;
	if (c.pwd_l >= 0)
	{
		c.oldpath = ft_calloc(ft_strlen(envp->env_shell[c.pwd_l]) + 1, 1);
		ft_strlcpy(c.oldpath, envp->env_shell[c.pwd_l],
			ft_strlen(envp->env_shell[c.pwd_l]) + 1);
	}
	if (builtin_cd2(&arg, &c, envp, ft_strlen(c.oldpath))
		|| builtin_cd3(&c, envp))
		return (1);
	if (c.oldpath)
	{
		free(envp->env_shell[c.oldpwd_l]);
		envp->env_shell[c.oldpwd_l] = new_oldpwd(c.oldpath);
		free(c.oldpath);
	}
	if (c.newpath)
		free(c.newpath);
	return (0);
}
