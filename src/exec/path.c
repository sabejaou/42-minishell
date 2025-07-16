/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:20 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:21 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_array_to_path(t_envp *envp, char **path_array, \
			char *str_cmd);
static void	check_path_error(t_envp *envp, int error, char *str_cmd, \
			char *path_cmd);
static char	*parse_env_and_path(t_envp *envp, char *str_cmd);
static char	*check_abs_path(char *str_cmd, t_envp *envp);

void	search_path(t_pipesep *seps, t_envp *envp)
{
	char	*str_cmd;
	char	*tmp;

	if (seps->cmd && seps->cmd[0])
		str_cmd = ft_strdup(seps->cmd[0]);
	else
		str_cmd = NULL;
	if (str_cmd == NULL)
	{
		seps->cmd[0] = NULL;
		return ;
	}
	else
	{
		if (bool_search_cmd(str_cmd, '/') == 0)
			tmp = parse_env_and_path(envp, str_cmd);
		else
			tmp = check_abs_path(str_cmd, envp);
		if (tmp)
			seps->cmd[0] = tmp;
	}
	free(str_cmd);
	str_cmd = NULL;
}

static char	*parse_env_and_path(t_envp *envp, char *str_cmd)
{
	char	**path_array;
	char	*join_cmd;
	int		i;

	path_array = NULL;
	join_cmd = NULL;
	i = 0;
	while (envp->env_shell && envp->env_shell[i])
	{
		if (ft_strncmp("PATH=", envp->env_shell[i], 5) == 0)
		{
			path_array = ft_split(envp->env_shell[i] + 5, ':');
			if (path_array == NULL)
				return (NULL);
		}
		i++;
	}
	join_cmd = parse_array_to_path(envp, path_array, str_cmd);
	free_dbtab(path_array);
	return (join_cmd);
}

static char	*parse_array_to_path(t_envp *envp, char **path_array, char *str_cmd)
{
	int			i;
	char		*join_cmd;
	struct stat	file_dir;

	join_cmd = NULL;
	i = 0;
	while (path_array && path_array[i])
	{
		free(join_cmd);
		join_cmd = ft_join_cmd(path_array[i], str_cmd);
		if (join_cmd == NULL)
			return (NULL);
		if (access(join_cmd, F_OK | X_OK | R_OK) == 0
			&& stat(join_cmd, &file_dir) == 0
			&& !S_ISDIR(file_dir.st_mode))
			return (join_cmd);
		i++;
	}
	ft_dprintf(2, "command not found : %s\n", str_cmd);
	envp->exit_status = 127;
	free(join_cmd);
	return (NULL);
}

static char	*check_abs_path(char *str_cmd, t_envp *envp)
{
	char		*path_cmd;
	size_t		i;
	struct stat	file_dir;

	path_cmd = ft_strdup(str_cmd);
	if (path_cmd == NULL)
		return (NULL);
	if (access(path_cmd, F_OK | X_OK | R_OK) != 0)
	{
		i = ft_protect_strlen(path_cmd);
		if (path_cmd[i - 1] == '/')
			check_path_error(envp, 2, str_cmd, path_cmd);
		else if (access(path_cmd, F_OK) == -1)
			check_path_error(envp, 3, str_cmd, path_cmd);
		else if (access(path_cmd, X_OK) == -1)
			check_path_error(envp, 4, str_cmd, path_cmd);
	}
	else if (access(path_cmd, F_OK | X_OK | R_OK) == 0
		&& stat(path_cmd, &file_dir) == 0 && S_ISDIR(file_dir.st_mode))
		check_path_error(envp, 1, str_cmd, path_cmd);
	else
		return (path_cmd);
	return (NULL);
}

static void	check_path_error(t_envp *envp, int error, char *str_cmd, \
			char *path_cmd)
{
	if (error == 1)
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", str_cmd);
		free(path_cmd);
		envp->exit_status = 126;
		return ;
	}
	else if (error == 2)
	{
		ft_dprintf(2, "minishell: %s: Not a directory\n", str_cmd);
		free(path_cmd);
		return ;
	}
	else if (error == 3)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", str_cmd);
		free(path_cmd);
		path_cmd = NULL;
		envp->exit_status = 127;
	}
	else if (error == 4)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", path_cmd);
		envp->exit_status = 126;
	}
}
